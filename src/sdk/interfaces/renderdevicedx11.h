#pragma once

class IRenderDeviceDx11
{
public:
	IRenderDeviceDx11() = delete;
	IRenderDeviceDx11(IRenderDeviceDx11&&) = delete;
	IRenderDeviceDx11(const IRenderDeviceDx11&) = delete;

	ID3D11Device* GetD3DDevice()
	{
		return reinterpret_cast<ID3D11Device*>(reinterpret_cast<std::uintptr_t>(this) + 0x28E50);
	}
};