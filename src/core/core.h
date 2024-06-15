#pragma once

class Core 
{
public:
	Core();
	~Core();

private:
	Address_t GetInterface(std::string_view moduleName, std::string_view interfaceName)
	{
		class InterfaceRegister
		{
		public:
			InterfaceRegister() = delete;
			InterfaceRegister(InterfaceRegister&&) = delete;
			InterfaceRegister(const InterfaceRegister&) = delete;

			void* (*pfnCreate)();
			const char* szName;
			InterfaceRegister* pNext;
		};

		Address_t moduleBaseAddress = pMemory->GetModuleBaseAddress(moduleName);
		if (!moduleBaseAddress)
		{
			pConsole->DebugOutput("?", "failed to find {} module", moduleName);
			return nullptr;
		}

		Address_t createInterfaceAddress = pMemory->GetExportAddress(moduleBaseAddress, "CreateInterface");
		if (!createInterfaceAddress)
		{
			pConsole->DebugOutput("?", "failed to find \"CreateInterface\" in {} module", moduleName);
			return nullptr;
		}

		const InterfaceRegister* interfaceRegister = createInterfaceAddress.Jump(0x3).Get<InterfaceRegister*>();

		for (; interfaceRegister; interfaceRegister = interfaceRegister->pNext)
		{
			if ((std::string_view(interfaceRegister->szName).compare(0, interfaceName.length(), interfaceName) == 0 && std::atoi(interfaceRegister->szName + interfaceName.length()) > 0) ||
				interfaceName.compare(interfaceRegister->szName) == 0)
				return Address_t(interfaceRegister->pfnCreate());
		}

		pConsole->DebugOutput("?", "failed to find {} interface in {} module", interfaceName, moduleName);
		return nullptr;
	}

};

inline std::unique_ptr<Core> pCore = nullptr;