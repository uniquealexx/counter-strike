#pragma once

class Core 
{
public:
	Core();
#ifdef _DEBUG
	~Core();
#endif
private:

};

inline std::unique_ptr<Core> pCore = nullptr;