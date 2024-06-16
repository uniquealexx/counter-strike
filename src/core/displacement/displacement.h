#pragma once

class Displacement
{
public:
	Displacement();

	struct
	{
		Address_t RenderDeviceDx11 = nullptr;

	} *Interfaces;

	struct
	{
		Address_t Present = nullptr;
		Address_t ResizeBuffers = nullptr;

	} *IDXGISwapChain;

};

inline std::unique_ptr<Displacement> pDisplacement = nullptr;