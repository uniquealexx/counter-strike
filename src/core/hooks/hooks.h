#pragma once

class Hooks
{
public:
	Hooks();
	~Hooks();

private:
	static void* HookFunction(void* target, void* detour);
	static void* HookVirtualFunction(void* instance, std::uint32_t index, void* detour);
};

inline std::unique_ptr<Hooks> pHooks = nullptr;