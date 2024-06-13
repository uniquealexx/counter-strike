#include "../../includes/includes.h"

#ifdef _DEBUG

Console::Console()
{
	hOldOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hOldErr = GetStdHandle(STD_ERROR_HANDLE);
	hOldIn = GetStdHandle(STD_INPUT_HANDLE);

	AllocConsole();
	AttachConsole(GetCurrentProcessId());

	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	hErr = GetStdHandle(STD_ERROR_HANDLE);
	hIn = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hOut, ENABLE_PROCESSED_OUTPUT | ENABLE_WRAP_AT_EOL_OUTPUT);

	SetConsoleMode(hIn, ENABLE_INSERT_MODE | ENABLE_EXTENDED_FLAGS | ENABLE_PROCESSED_INPUT | ENABLE_QUICK_EDIT_MODE);
}

Console::~Console()
{
	if (!hOut || !hErr || !hIn)
		return;

	FreeConsole();

	if (hOldOut) SetStdHandle(STD_OUTPUT_HANDLE, hOldOut);
	if (hOldErr) SetStdHandle(STD_ERROR_HANDLE, hOldErr);
	if (hOldIn) SetStdHandle(STD_INPUT_HANDLE, hOldIn);
}

#endif // _DEBUG
