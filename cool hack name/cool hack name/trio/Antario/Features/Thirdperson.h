#pragma once
#include "..\GUI\Keybind.h"
#include "..\Settings.h"
#include "..\Utils\Interfaces.h"
#include "..\Utils\Math.h"
#include "..\SDK\IEngineTrace.h"

class thirdperson
{
public:
	bool bThirdperson = false;
	void doThirdperson();
};

extern thirdperson g_thirdperson;