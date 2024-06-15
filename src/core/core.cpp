#include "../includes/includes.h"

Core::Core()
{
#ifdef _DEBUG
	pConsole = std::make_unique<Console>();
	pConsole->DebugOutput("~", "init {} complete", typeid(Console).name());
#endif // _DEBUG
	pInterfaces = std::make_unique<Interfaces>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Interfaces).name());
#endif // _DEBUG
	pHooks = std::make_unique<Hooks>();
#ifdef _DEBUG
	pConsole->DebugOutput("~", "init {} complete", typeid(Hooks).name());
#endif // _DEBUG
}

Core::~Core()
{
#ifdef _DEBUG
	pConsole->DebugOutput("~", "unload cheat...");
#endif // _DEBUG
	pInterfaces.reset();
	pHooks.reset();
#ifdef _DEBUG
	pConsole.reset();
#endif // _DEBUG
}
