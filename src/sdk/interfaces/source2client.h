#pragma once

class ISource2Client : public IAppSystem
{
	ISource2Client() = delete;
	ISource2Client(ISource2Client&&) = delete;
	ISource2Client(const ISource2Client&) = delete;
};