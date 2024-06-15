#pragma once

class Hooks
{
public:
	Hooks();
	~Hooks();

private:
	static void* HookFunction(void* target, void* detour);
	static void* HookVirtualFunction(void* instance, std::uint32_t index, void* detour);

	template <typename T>
	T CreateHook(void* target, T detour) 
	{
		return reinterpret_cast<T>(HookFunction(target, reinterpret_cast<void*>(detour)));
	}

	template <typename T>
	T CreateVirtualHook(void* instance, std::uint32_t index, T detour) 
	{
		return reinterpret_cast<T>(HookVirtualFunction(instance, index, reinterpret_cast<void*>(detour)));
	}

private:
#pragma region virtual_hook
	static void FrameStageNotify(ISource2Client* pSource2Client, int iFrameStage);
	static inline decltype(&FrameStageNotify) pfnFrameStageNotify = nullptr;
#pragma endregion

#pragma region detour_hook

#pragma endregion

};

inline std::unique_ptr<Hooks> pHooks = nullptr;