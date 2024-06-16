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
	static inline decltype(&FrameStageNotify) fnFrameStageNotify = nullptr;
#pragma endregion

#pragma region detour_hook
	static std::int32_t Present(IDXGISwapChain* swapChain, std::uint32_t syncInterval, std::uint32_t flags);
	static inline decltype(&Present) fnPresent = nullptr;

	static std::int32_t ResizeBuffers(IDXGISwapChain* swapChain, std::uint32_t bufferCount, std::uint32_t width, std::uint32_t height, std::int32_t newFormat, std::uint32_t swapChainFlags);
	static inline decltype(&ResizeBuffers) fnResizeBuffers = nullptr;
#pragma endregion

};

inline std::unique_ptr<Hooks> pHooks = nullptr;