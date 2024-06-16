#pragma once

class Input
{
public:
	Input();
	~Input();

	HWND GetGameWindow();

private:
	HWND gameWindow = nullptr;

};

inline std::unique_ptr<Input> pInput = nullptr;