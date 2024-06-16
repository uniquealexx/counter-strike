#include "../../includes/includes.h"

Displacement::Displacement()
{
	Interfaces->RenderDeviceDx11 = Memory::FindPattern("client.dll", "48 8B 0D ? ? ? ? 66 44 89 6C 24").Jump(0x3);

	IDXGISwapChain->Present = Memory::FindPattern("gameoverlayrenderer64.dll", "48 89 6C 24 ? 48 89 74 24 ? 41 56 48 83 EC 20 41 8B E8");
	IDXGISwapChain->ResizeBuffers = Memory::FindPattern("gameoverlayrenderer64.dll", "48 89 5C 24 ? 48 89 6C 24 ? 48 89 74 24 ? 57 41 56 41 57 48 83 EC ? 44 8B FA");
}
