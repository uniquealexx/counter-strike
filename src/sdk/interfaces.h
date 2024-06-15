#pragma once

class Interfaces
{
public:
	Interfaces()
	{
		pSource2Client = GetInterface("client.dll", "Source2Client").Cast<ISource2Client*>();
		pSource2Engine = GetInterface("engine2.dll", "Source2EngineToClient").Cast<ISource2Engine*>();
	}

	~Interfaces()
	{
		delete pSource2Client;
		delete pSource2Engine;
	}

	ISource2Client* pSource2Client = nullptr;;
	ISource2Engine* pSource2Engine = nullptr;;

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

		Address_t moduleBaseAddress = Memory::GetModuleBaseAddress(moduleName);
		if (!moduleBaseAddress)
		{
			pConsole->DebugOutput("?", "failed to find {} module", moduleName);
			return nullptr;
		}

		Address_t createInterfaceAddress = Memory::GetExportAddress(moduleBaseAddress, "CreateInterface");
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

inline std::unique_ptr<Interfaces> pInterfaces = nullptr;