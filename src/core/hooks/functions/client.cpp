#include "../../../includes/includes.h"

void Hooks::FrameStageNotify(ISource2Client* pSource2Client, int iFrameStage)
{
    fnFrameStageNotify(pSource2Client, iFrameStage);

	if (iFrameStage == FRAME_RENDER_START)
	{
		// BeginFrame

		// FinishFrame
	}
}