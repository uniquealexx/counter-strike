#pragma once
class Render
{
public:
	Render();
	~Render();

	void PrePresent(IDXGISwapChain* pSwapChain);
	void PostPresent();

	// realize later
	void BeginFrame();
	void FinishFrame();

private:
	Microsoft::WRL::ComPtr<ID3D11Device> m_pD3D11Device = nullptr;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> m_pD3D11DeviceContext = nullptr;

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pRenderTargetView = nullptr;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> m_pBackupRenderTargetView = nullptr;
};

inline std::unique_ptr<Render> pRender = nullptr;