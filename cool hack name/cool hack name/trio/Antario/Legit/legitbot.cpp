#include "legitbot.h"
#include "../Utils/GlobalVars.h"
#include "../Settings.h"
#include "../SDK/CInput.h"
#include "../SDK/Studio.h"
//#include "..\autowall\autowall.h"
#include "../SDK/CGlobalVarsBase.h"
#include "../Utils/Math.h"
#include "../SDK/CEntity.h"

void c_legitbot::aim(CUserCmd* cmd) {
	float best_fov = g_Settings.rage.lbot_fov;
	Vector view_angles, engine_angles, angles, smooth_angle;

	if (g_Settings.rage.lbot_enable)
	{
		if (GetAsyncKeyState(VK_LBUTTON))
			return;

		for (int i = 1; i <= g_pEngine->GetMaxClients(); ++i)
		{
			C_BaseEntity* e = g_pEntityList->GetClientEntity(i);

			//Sanity check
			if (!e || e->IsDormant() || !e->IsAlive() || e == g::pLocalEntity || e->GetTeam() == g::pLocalEntity->GetTeam())
				continue;

			//Viewangles
			g_pEngine->GetViewAngles(engine_angles);

			//Getting the bone to aim at
			switch (g_Settings.rage.lbot_hitbox)
			{
			case 0:
				angles = g_Math.NormalizeAngle(g_Math.CalcAngle(g::pLocalEntity->GetEyePosition(), e->GetBonePos(8)));//head
				break;
			case 1:
				angles = g_Math.NormalizeAngle(g_Math.CalcAngle(g::pLocalEntity->GetEyePosition(), e->GetBonePos(6)));//body
				break;
			}

			float fov = (engine_angles - angles).Length2D();

			if (fov < best_fov)
			{
				best_fov = fov;
				view_angles = angles;
			}
		}

		if (g_Settings.rage.lbot_smoothbox)
		{
			smooth_angle = engine_angles - view_angles;
			g_Math.NormalizeAngle(smooth_angle);
			g_Math.ClampAngles(smooth_angle);
			view_angles = engine_angles - smooth_angle / (g_Settings.rage.lbot_smooth);
		}

		//Making sure they are in view
		if (best_fov != g_Settings.rage.lbot_fov)
		{
			if (g_Settings.rage.lbot_silentaim)
				cmd->viewangles = view_angles;
		}
	}
}

c_legitbot legitbot;