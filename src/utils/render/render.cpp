#include "../../includes/includes.h"

Render::Render()
{
	m_pD3D11Device = pInterfaces->pRenderDeviceDx11->GetD3DDevice();

	if (!m_pD3D11Device)
	{
		pConsole->DebugOutput("?", "failed to get d3d11 device");
		return;
	}

	m_pD3D11Device->GetImmediateContext(&m_pD3D11DeviceContext);

	if (!m_pD3D11DeviceContext)
	{
		pConsole->DebugOutput("?", "failed to get d3d11 device context");
		return;
	}

	ImGui::CreateContext();

	ImGui_ImplWin32_Init(pInput->GetGameWindow());
	ImGui_ImplDX11_Init(m_pD3D11Device.Get(), m_pD3D11DeviceContext.Get());
}

Render::~Render()
{
	if (ImGui::GetCurrentContext())
	{
		ImGui_ImplDX11_Shutdown();
		ImGui_ImplWin32_Shutdown();

		ImGui::DestroyContext();
	}
}

void Render::PrePresent(IDXGISwapChain* pSwapChain)
{
	Microsoft::WRL::ComPtr< ID3D11Texture2D > pBackBuffer = nullptr;
	if (FAILED(pSwapChain->GetBuffer(0, IID_PPV_ARGS(&pBackBuffer))))
		return;

	D3D11_RENDER_TARGET_VIEW_DESC d3d11RenderTargetViewDesc;
	std::memset(&d3d11RenderTargetViewDesc, 0, sizeof(d3d11RenderTargetViewDesc));
	d3d11RenderTargetViewDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	d3d11RenderTargetViewDesc.ViewDimension = D3D11_RTV_DIMENSION_TEXTURE2DMS;

	m_pD3D11Device->CreateRenderTargetView(pBackBuffer.Get(), &d3d11RenderTargetViewDesc, &m_pRenderTargetView);

	m_pD3D11DeviceContext->OMGetRenderTargets(1, m_pBackupRenderTargetView.GetAddressOf(), nullptr);
	m_pD3D11DeviceContext->OMSetRenderTargets(1, m_pRenderTargetView.GetAddressOf(), nullptr);

	// render objects
}

void Render::PostPresent()
{
	if (!m_pRenderTargetView)
		return;

	m_pD3D11DeviceContext->OMSetRenderTargets(1, m_pBackupRenderTargetView.GetAddressOf(), nullptr);
	m_pBackupRenderTargetView.Reset();
	m_pRenderTargetView.Reset();
}
