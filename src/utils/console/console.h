#pragma once

#ifdef _DEBUG

class Console
{
public:
	Console();
	~Console();

    template <typename... Args>
    void DebugOutput(std::string_view prefix, std::string_view message, Args... args)
    {
        std::string combinedMessage = std::format("[{}] {}\n", prefix, 
                                      std::vformat(message, std::make_format_args(args...)));

        HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
        if (hOut == INVALID_HANDLE_VALUE)
        {
            std::cerr << "Error getting console handle\n";
            return;
        }

        SetConsoleTextAttribute(hOut, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);

        DWORD bytesWritten;
        if (!WriteConsoleA(hOut, combinedMessage.data(), static_cast<DWORD>(combinedMessage.size()), &bytesWritten, nullptr))
            std::cerr << "Error writing debug output message to console\n";
    }

private:
	HANDLE hOut;
	HANDLE hErr;
	HANDLE hIn;
	HANDLE hOldErr;
	HANDLE hOldOut;
	HANDLE hOldIn;
};

inline std::unique_ptr<Console> pConsole = nullptr;

#endif // _DEBUG

