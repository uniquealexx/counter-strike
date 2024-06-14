#pragma once

struct Address_t
{
	Address_t() = default;
	~Address_t() = default;

	Address_t(std::uintptr_t address) : uAddress(address) {}
	Address_t(const void* address) : uAddress(reinterpret_cast<std::uintptr_t>(address)) {}

	operator std::uintptr_t() { return uAddress; }
	operator bool() { return uAddress; }

	operator void* () { return reinterpret_cast<void*>(uAddress); }

	template <typename T = Address_t>
	constexpr T Offset(std::ptrdiff_t offset)
	{
		return T(uAddress + offset);
	}

	template <typename T = Address_t>
	inline T Get(std::uint32_t dereferenceCount = 1) 
	{
		std::uintptr_t outAddress = uAddress;

		while (dereferenceCount-- && outAddress)
			outAddress = *reinterpret_cast<std::uintptr_t*>(outAddress);

		return T(outAddress);
	}

	template <typename T = Address_t>
	inline T Jump(std::ptrdiff_t offset = 0x1) 
	{
		std::uintptr_t outAddress = uAddress + offset;

		outAddress += *reinterpret_cast<std::int32_t*>(outAddress);
		outAddress += 4;

		return T(outAddress);
	}

	template <typename T = std::uintptr_t>
	constexpr T Cast()
	{
		return T(uAddress);
	}
private:
	std::uintptr_t uAddress = 0u;
};

class Memory
{
public:
	Address_t GetModuleBaseAddress(std::string_view moduleName);
	Address_t GetModuleBaseAddress(std::wstring_view moduleName);

	Address_t GetExportAddress(Address_t moduleBaseAddress, std::string_view procedureName);

	bool GetSectionInfo(Address_t moduleAddress, std::string_view sectionName, Address_t* outSectionAddress, std::size_t* outSectionSize);

	Address_t FindPattern(std::string_view moduleName, std::string_view pattern);
	Address_t FindPattern(Address_t regionAddress, std::size_t regionSize, std::string_view pattern);

	std::vector<std::optional<std::byte>> PatternToBytes(std::string_view pattern);

private:

};

inline std::unique_ptr<Memory> pMemory = nullptr;