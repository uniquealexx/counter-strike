#include "../../includes/includes.h"

Hooks::Hooks()
{
	MH_Initialize();

	MH_EnableHook(MH_ALL_HOOKS);
}

Hooks::~Hooks()
{
	MH_DisableHook(MH_ALL_HOOKS);

	MH_Uninitialize();
}

void* Hooks::HookFunction(void* target, void* detour)
{
	void* original = nullptr;

	if (const MH_STATUS status = MH_CreateHook(target, detour, &original); status != MH_OK)
	{
		pConsole->DebugOutput("?", "failed to hook function {}", MH_StatusToString(status));
		return nullptr;
	}

	return original;
}

void* Hooks::HookVirtualFunction(void* instance, std::uint32_t index, void* detour)
{
	void* original = nullptr;

	if (const MH_STATUS status = MH_CreateHook((*reinterpret_cast<void***>(instance))[index], detour, &original); status != MH_OK)
	{
		pConsole->DebugOutput("?", "failed to hook virtual function {}", MH_StatusToString(status));
		return nullptr;
	}

	return original;
}
