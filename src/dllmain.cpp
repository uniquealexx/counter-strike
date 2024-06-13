#include "includes/includes.h"

#ifdef _DEBUG
void DllDetach(HMODULE module);
#endif // _DEBUG
void DllAttach(HMODULE module)
{
    pCore = std::make_unique<Core>();

#ifdef _DEBUG
    if (pCore)
    {
        while (!GetAsyncKeyState(VK_F11))
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

        std::thread(DllDetach, module).detach();
    }
#endif // _DEBUG
}

#ifdef _DEBUG
void DllDetach(HMODULE module)
{
    pCore.reset();

    FreeLibrary(module);
}
#endif // _DEBUG

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        std::thread(DllAttach, module).detach();

    return TRUE;
}
