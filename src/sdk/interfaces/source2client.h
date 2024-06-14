#pragma once

enum ClientFrameStage
{
	FRAME_RENDER_START = 9,
};

class ISource2Client : public IAppSystem
{
	ISource2Client() = delete;
	ISource2Client(ISource2Client&&) = delete;
	ISource2Client(const ISource2Client&) = delete;
};