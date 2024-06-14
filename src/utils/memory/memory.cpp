#include "../../includes/includes.h"

PEB* GetProcessEnvironmentBlock()
{
	return reinterpret_cast<PEB*>(__readgsqword(0x60));
}

Address_t Memory::GetModuleBaseAddress(std::string_view moduleName)
{
	std::unique_ptr wideString = std::make_unique<std::wstring_view::value_type[]>(moduleName.length());
	std::size_t length = std::mbstowcs(wideString.get(), moduleName.data(), moduleName.length());
	return GetModuleBaseAddress(std::wstring_view(wideString.get(), length));
}

Address_t Memory::GetModuleBaseAddress(std::wstring_view moduleName)
{
	PEB* processEnvironmentBlock = GetProcessEnvironmentBlock();

	if (!processEnvironmentBlock)
		return nullptr; 

	LIST_ENTRY* moduleList = &processEnvironmentBlock->Ldr->InMemoryOrderModuleList;

	for (LIST_ENTRY* listEntry = moduleList->Flink; listEntry != moduleList; listEntry = listEntry->Flink)
	{
		LDR_DATA_TABLE_ENTRY* entry = CONTAINING_RECORD(listEntry, LDR_DATA_TABLE_ENTRY, InMemoryOrderLinks);

		if (!entry)
			continue;

		std::wstring_view modulePath(entry->FullDllName.Buffer);
		std::size_t lastDelimiter = modulePath.find_last_of('\\');

		if (lastDelimiter == std::wstring_view::npos)
			continue;

		if (modulePath.substr(lastDelimiter + 1) != moduleName)
			continue;

		return Address_t(entry->DllBase);
	}

	return nullptr;
}

Address_t Memory::GetExportAddress(Address_t moduleBaseAddress, std::string_view procedureName)
{
	auto* DOSHeader = moduleBaseAddress.Cast< const IMAGE_DOS_HEADER* >();
	auto* NTHeaders = moduleBaseAddress.Offset< const IMAGE_NT_HEADERS* >(DOSHeader->e_lfanew);

	const IMAGE_OPTIONAL_HEADER* optionalHeader = &NTHeaders->OptionalHeader;

	const std::uint32_t exportSize = optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].Size;
	const std::uint32_t exportAddress = optionalHeader->DataDirectory[IMAGE_DIRECTORY_ENTRY_EXPORT].VirtualAddress;

	if (exportSize <= 0)
		return nullptr;

	auto* exportDirectory = moduleBaseAddress.Offset< const IMAGE_EXPORT_DIRECTORY* >(exportAddress);
	auto* namesRVA = moduleBaseAddress.Offset< const std::uint32_t* >(exportDirectory->AddressOfNames);
	auto* functionsRVA = moduleBaseAddress.Offset< const std::uint32_t* >(exportDirectory->AddressOfFunctions);
	auto* nameOrdinalsRVA = moduleBaseAddress.Offset< const std::uint16_t* >(exportDirectory->AddressOfNameOrdinals);

	std::uint32_t right = exportDirectory->NumberOfNames;
	std::uint32_t left = 0;

	while (right != left)
	{
		const std::uint32_t middle = left + ((right - left) >> 1);
		const int result = procedureName.compare(moduleBaseAddress.Offset< const char* >(namesRVA[middle]));

		if (result > 0) left = middle;
		else if (result < 0) right = middle;
		else return moduleBaseAddress.Offset(functionsRVA[nameOrdinalsRVA[middle]]);
	}

	return nullptr;
}

bool Memory::GetSectionInfo(Address_t moduleAddress, std::string_view sectionName, Address_t* outSectionAddress, std::size_t* outSectionSize)
{
	auto* const DOSHeader = moduleAddress.Cast< const IMAGE_DOS_HEADER* >();
	auto* const NTHeaders = moduleAddress.Offset< const IMAGE_NT_HEADERS* >(DOSHeader->e_lfanew);

	const IMAGE_FILE_HEADER* const fileHeader = &NTHeaders->FileHeader;

	for (std::uint16_t sectionIndex = 0; sectionIndex < fileHeader->NumberOfSections; sectionIndex++)
	{
		auto* const section = Address_t(&NTHeaders->OptionalHeader).Offset< const IMAGE_SECTION_HEADER* >(NTHeaders->FileHeader.SizeOfOptionalHeader + sizeof(IMAGE_SECTION_HEADER) * sectionIndex);

		const std::string_view name(reinterpret_cast<const char*>(section->Name));

		if (name == sectionName)
		{
			if (outSectionAddress)
				*outSectionAddress = moduleAddress.Offset(section->VirtualAddress);

			if (outSectionSize)
				*outSectionSize = section->Misc.VirtualSize;

			return true;
		}
	}

	return false;
}

Address_t Memory::FindPattern(std::string_view moduleName, std::string_view pattern)
{
	Address_t moduleAddress = GetModuleBaseAddress(moduleName);

	if (!moduleAddress)
		return nullptr;

	Address_t codeSection = nullptr;
	std::size_t sectionSize = 0;

	if (!GetSectionInfo(moduleAddress, ".text", &codeSection, &sectionSize))
		return nullptr;

	return FindPattern(codeSection, sectionSize, pattern);
}

Address_t Memory::FindPattern(Address_t regionAddress, std::size_t regionSize, std::string_view pattern)
{
	const std::byte* const bytes = regionAddress.Cast< std::byte* >();

	const std::vector< std::optional< std::byte > > listBytes = PatternToBytes(pattern);

	if (listBytes.empty())
		return nullptr;

	for (std::uintptr_t index = 0, size = regionSize - listBytes.size(); index < size; ++index)
	{
		bool byteFound = true;

		for (std::size_t byteIndex = 0; byteIndex < listBytes.size(); ++byteIndex)
		{
			if (!listBytes[byteIndex].has_value())
				continue;

			if (bytes[index + byteIndex] == listBytes[byteIndex].value())
				continue;

			byteFound = false;
			break;
		}

		if (byteFound)
			return Address_t(reinterpret_cast<const void*>(&bytes[index]));
	}

	return nullptr;
}

std::vector<std::optional<std::byte>> Memory::PatternToBytes(std::string_view pattern)
{
	std::vector<std::optional<std::byte>> listBytes = { };

	const char* start = pattern.data();
	const char* end = start + pattern.size();

	for (const char* current = start; current < end; ++current)
	{
		if (*current == '?')
		{
			++current;
			if (*current == '?') 
				++current;

			listBytes.emplace_back(std::nullopt);
		}
		else 
			listBytes.emplace_back(static_cast<std::byte>(std::strtoul(current, const_cast<char**>(&current), 16)));
	}

	return listBytes;
}
