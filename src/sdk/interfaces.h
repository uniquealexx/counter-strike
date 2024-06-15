#pragma once

struct Interfaces
{
    ISource2Client* pSource2Client = nullptr;;
    ISource2Engine* pSource2Engine = nullptr;;
};

inline std::unique_ptr<Interfaces> pInterfaces = nullptr;