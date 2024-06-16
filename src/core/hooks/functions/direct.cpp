#include "../../../includes/includes.h"

std::int32_t Hooks::Present(IDXGISwapChain* swapChain, std::uint32_t syncInterval, std::uint32_t flags)
{
	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	pRender->PrePresent(swapChain);

	ImGui::Render();

	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	auto original = fnPresent(swapChain, syncInterval, flags);

	pRender->PostPresent();

	return original;
}

std::int32_t Hooks::ResizeBuffers(IDXGISwapChain* swapChain, std::uint32_t bufferCount, std::uint32_t width, std::uint32_t height, std::int32_t newFormat, std::uint32_t swapChainFlags)
{
	return fnResizeBuffers(swapChain, bufferCount, width, height, newFormat, swapChainFlags);
}
