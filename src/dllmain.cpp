#include "includes/includes.h"

void DllDetach(HMODULE module);
void DllAttach(HMODULE module)
{
    pCore = std::make_unique<Core>();

    if (pCore)
    {
        while (!GetAsyncKeyState(VK_F11))
            std::this_thread::sleep_for(std::chrono::milliseconds(200));

        std::thread(DllDetach, module).detach();
    }
}

void DllDetach(HMODULE module)
{
    FreeLibrary(module);
}

BOOL APIENTRY DllMain(HMODULE module, DWORD reason, LPVOID reserved)
{
    if (reason == DLL_PROCESS_ATTACH)
        std::thread(DllAttach, module).detach();

    return TRUE;
}
