#include "Common/Profiler/Profiler.h"
#include "Common/Log.h"
#include "Common/TimeUtil.h"

#include "Core/RetroAchievements.h"
#include "Core/CoreParameter.h"
#include "Core/Core.h"
#include "Core/Config.h"
#include "Core/HW/Display.h"
#include "Core/FrameTiming.h"

FrameTiming g_frameTiming;

inline Draw::PresentMode GetBestImmediateMode(Draw::PresentMode supportedModes) {
	if (supportedModes & Draw::PresentMode::MAILBOX) {
		return Draw::PresentMode::MAILBOX;
	}
	else {
		return Draw::PresentMode::IMMEDIATE;
	}
}

void FrameTiming::Reset(Draw::DrawContext* draw) {
	if (g_Config.bVSync || !(draw->GetDeviceCaps().presentModesSupported & (Draw::PresentMode::MAILBOX | Draw::PresentMode::IMMEDIATE))) {
		presentMode = Draw::PresentMode::FIFO;
		presentInterval = 1;
	}
	else {
		presentMode = GetBestImmediateMode(draw->GetDeviceCaps().presentModesSupported);
		presentInterval = 0;
	}
}

Draw::PresentMode ComputePresentMode(Draw::DrawContext* draw, int* interval) {
	Draw::PresentMode mode = Draw::PresentMode::FIFO;

	if (draw->GetDeviceCaps().presentModesSupported & (Draw::PresentMode::IMMEDIATE | Draw::PresentMode::MAILBOX)) {
		// Switch to immediate if desired and possible.
		bool wantInstant = false;
		if (!g_Config.bVSync) {
			wantInstant = true;
		}

		if (PSP_CoreParameter().fastForward) {
			wantInstant = true;
		}

		if (g_Config.bRenderSkip3 && g_Config.iFpsLimit1State) {
			wantInstant = true;
		}else
		if (PSP_CoreParameter().fpsLimit != FPSLimit::NORMAL) {
			int limit;
			if (PSP_CoreParameter().fpsLimit == FPSLimit::CUSTOM1 || g_Config.iFpsLimit1State)
				limit = g_Config.iFpsLimit1;
			else if (PSP_CoreParameter().fpsLimit == FPSLimit::CUSTOM2 || g_Config.iFpsLimit2State)
				limit = g_Config.iFpsLimit2;
			else
				limit = PSP_CoreParameter().analogFpsLimit;

			// For an alternative speed that is a clean factor of 60, the user probably still wants vsync.
			// TODO: Should take the user's display refresh rate into account...
			if (limit == 0 || (limit >= 0 && limit != 15 && limit != 30 && limit != 60 && limit != g_Config.iRefreshRate2)) {
				wantInstant = true;
			}
		}

		if (wantInstant && g_Config.bVSync && !draw->GetDeviceCaps().presentInstantModeChange) {
			// If in vsync mode (which will be FIFO), and the backend can't switch immediately,
			// stick to FIFO.
			wantInstant = false;
		}

		// The outer if checks that instant modes are available.
		if (wantInstant) {
			mode = GetBestImmediateMode(draw->GetDeviceCaps().presentModesSupported);
		}
	}

	*interval = (mode == Draw::PresentMode::FIFO) ? 1 : 0;
	return mode;
}
