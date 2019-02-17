#pragma once

#include "autowall.h"
#include "aimbot.h"
#include "../Hooks.h"
#include "../SDK/IVModelInfoClient.h"
#include "..\Settings.h"
#include "..\SDK\CGlobalVarsBase.h"
#include "../SDK/Cvar.h"

class c_antiaim
{
public:

	void slow_move(CUserCmd * cmd);
	void fakelag();
	void anti_aim();

};

extern c_antiaim antiaim;