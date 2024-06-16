#include "../includes/includes.h"

Core::Core()
{
#ifdef _DEBUG
	pConsole = std::make_unique<Console>();
	pConsole->DebugOutput("~", "init {} complete", typeid(Console).name());
#endif // _DEBUG
	pDisplacement = std::make_unique<Displacement>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Displacement).name());
#endif // _DEBUG
	pInterfaces = std::make_unique<Interfaces>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Interfaces).name());
#endif // _DEBUG
	pInput = std::make_unique<Input>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Input).name());
#endif // _DEBUG
	pRender = std::make_unique<Render>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Render).name());
#endif // _DEBUG
	pHooks = std::make_unique<Hooks>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Hooks).name());
#endif // _DEBUG
}

#ifdef _DEBUG

Core::~Core()
{
	pConsole->DebugOutput("~", "unload cheat...");
	pHooks.reset();
	pConsole.reset();
}

#endif // _DEBUG

