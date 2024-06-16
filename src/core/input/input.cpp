#include "../../includes/includes.h"

Input::Input()
{
	gameWindow = FindWindow(L"SDL_app", L"Counter-Strike 2");

	if (!gameWindow)
	{
		pConsole->DebugOutput("?", "failed to find Counter-Strike 2 window");
		return;
	}
}

Input::~Input()
{
	gameWindow = nullptr;
}

HWND Input::GetGameWindow()
{
	return gameWindow;
}
