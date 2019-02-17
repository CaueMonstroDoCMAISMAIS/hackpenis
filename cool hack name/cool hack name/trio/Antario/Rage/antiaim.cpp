#include "antiaim.h"
#include "../Utils/Math.h"

bool Swtich = false;

void c_antiaim::slow_move(CUserCmd* cmd) {
	auto velocity = g::pLocalEntity->GetVelocity().Length2D();
	auto weapon = g::pLocalEntity2->GetActiveWeapon(); 	if (!weapon) return;
	if (g_Settings.rage.slowwalk) {
		switch (g_Settings.rage.slowwalktype)
		{
		case 0:
			if (velocity >= (weapon->GetCSWpnData()->max_speed * .34))
			{
				if (GetAsyncKeyState(VK_LSHIFT))
				{
					cmd->buttons |= IN_WALK;
					cmd->forwardmove = -cmd->forwardmove;
					cmd->sidemove = -cmd->sidemove;
					cmd->upmove = 0;
				}
			}
			break;
		case 1:
			if (velocity >= (weapon->GetCSWpnData()->max_speed * .34))
			{
				if (GetAsyncKeyState(VK_LSHIFT))
				{
					cmd->buttons |= IN_WALK;
					cmd->forwardmove = -g::pCmd->forwardmove;
					cmd->sidemove = -g::pCmd->sidemove;
					cmd->upmove = 0;
				}
			}
			break;
		}
	}
}

void c_antiaim::fakelag() {
	static int ticks = 0;
	int choke;
	bool should_fakelag = false;

	switch (g_Settings.rage.flag_type) {
	case 0:
		choke = g_Settings.rage.flag_packets;
		break;
	case 1:
		choke = std::min<int>(static_cast<int>(std::ceilf(64 / (g::pLocalEntity->GetVelocity().Length() * g_pGlobalVars->intervalPerTick))), g_Settings.rage.flag_packets);
		break;
	}

	if (g_Settings.rage.flag_when[0]) {
		if (g::pLocalEntity->GetFlags() & FL_ONGROUND)
			should_fakelag = true;
	}

	if (g_Settings.rage.flag_when[1]) {
		if (g::pLocalEntity->GetVelocity().Length() > 0.1f && g::pLocalEntity->GetFlags() & FL_ONGROUND)
			should_fakelag = true;
	}

	if (g_Settings.rage.flag_when[2]) {
		if (!(g::pLocalEntity->GetFlags() & FL_ONGROUND))
			should_fakelag = true;
	}

	if (should_fakelag) {
		if (ticks > choke) {
			ticks = 0;
			g::bSendPacket = true;
		}
		else {
			g::bSendPacket = false;
			ticks++;
		}
		g::fakelag = true;
	}
	else
		g::fakelag = false;
}

void FreeStanding() // cancer v1
{
	static float FinalAngle;
	bool bside1 = false;
	bool bside2 = false;
	bool autowalld = false;
	for (int i = 1; i <= g_pEngine->GetMaxClients(); ++i)
	{
		C_BaseEntity* pPlayerEntity = g_pEntityList->GetClientEntity(i);

		if (!pPlayerEntity
			|| !pPlayerEntity->IsAlive()
			|| pPlayerEntity->IsDormant()
			|| pPlayerEntity == g::pLocalEntity
			|| pPlayerEntity->GetTeam() == g::pLocalEntity->GetTeam())
			continue;

		float angToLocal = g_Math.CalcAngle(g::pLocalEntity->GetOrigin(), pPlayerEntity->GetOrigin()).y;
		Vector ViewPoint = pPlayerEntity->GetOrigin() + Vector(0, 0, 90);

		Vector2D Side1 = { (45 * sin(g_Math.GRD_TO_BOG(angToLocal))),(45 * cos(g_Math.GRD_TO_BOG(angToLocal))) };
		Vector2D Side2 = { (45 * sin(g_Math.GRD_TO_BOG(angToLocal + 180))) ,(45 * cos(g_Math.GRD_TO_BOG(angToLocal + 180))) };

		Vector2D Side3 = { (50 * sin(g_Math.GRD_TO_BOG(angToLocal))),(50 * cos(g_Math.GRD_TO_BOG(angToLocal))) };
		Vector2D Side4 = { (50 * sin(g_Math.GRD_TO_BOG(angToLocal + 180))) ,(50 * cos(g_Math.GRD_TO_BOG(angToLocal + 180))) };

		Vector Origin = g::pLocalEntity->GetOrigin();

		Vector2D OriginLeftRight[] = { Vector2D(Side1.x, Side1.y), Vector2D(Side2.x, Side2.y) };

		Vector2D OriginLeftRightLocal[] = { Vector2D(Side3.x, Side3.y), Vector2D(Side4.x, Side4.y) };

		for (int side = 0; side < 2; side++)
		{
			Vector OriginAutowall = { Origin.x + OriginLeftRight[side].x,  Origin.y - OriginLeftRight[side].y , Origin.z + 80 };
			Vector OriginAutowall2 = { ViewPoint.x + OriginLeftRightLocal[side].x,  ViewPoint.y - OriginLeftRightLocal[side].y , ViewPoint.z };

			if (g_Autowall.CanHitFloatingPoint(OriginAutowall, ViewPoint))
			{
				if (side == 0)
				{
					bside1 = true;
					FinalAngle = angToLocal + 90;
				}
				else if (side == 1)
				{
					bside2 = true;
					FinalAngle = angToLocal - 90;
				}
				autowalld = true;
			}
			else
			{
				for (int side222 = 0; side222 < 2; side222++)
				{
					Vector OriginAutowall222 = { Origin.x + OriginLeftRight[side222].x,  Origin.y - OriginLeftRight[side222].y , Origin.z + 80 };

					if (g_Autowall.CanHitFloatingPoint(OriginAutowall222, OriginAutowall2))
					{
						if (side222 == 0)
						{
							bside1 = true;
							FinalAngle = angToLocal + 90;
						}
						else if (side222 == 1)
						{
							bside2 = true;
							FinalAngle = angToLocal - 90;
						}
						autowalld = true;
					}
				}
			}
		}
	}

	if (!autowalld || (bside1 && bside2))
		g::pCmd->viewangles.y += 180;
	else
		g::pCmd->viewangles.y = FinalAngle;

	if (g_Settings.rage.JitterRange != 0)
	{
		float Offset = g_Settings.rage.JitterRange / 2.f;

		if (!g_Settings.rage.RandJitterInRange)
		{
			Swtich ? g::pCmd->viewangles.y -= Offset : g::pCmd->viewangles.y += Offset;
		}
		else
		{
			static bool oldSwtich = Swtich;

			g::pCmd->viewangles.y -= Offset;

			static int Add = 0;

			if (oldSwtich != Swtich)
			{
				Add = rand() % g_Settings.rage.JitterRange;
				oldSwtich = Swtich;
			}

			g::pCmd->viewangles.y += Add;
		}
	}
}

void c_antiaim::anti_aim() {

	static bool Swtich2 = false;
	Swtich2 = !Swtich2;

	static float test = 0.f;
	if (Swtich2)
		test += 90.f;

	test = g_Math.NormalizeYaw(test);

	auto pitch = [&]() -> void
	{
		switch (g_Settings.rage.aapitch)
		{
		case 0: break;
		case 1: {
			g::pCmd->viewangles.x = 89;
		}
				break;
		}
	};
	auto real_yaw = [&]() -> void
	{
		switch (g_Settings.rage.aayaw)
		{
		case 0: break;
		case 1:
			static bool down, left, right;
			if (GetAsyncKeyState(VK_DOWN)) { down = true; left = false; right = false; }
			if (GetAsyncKeyState(VK_LEFT)) { down = false; left = true; right = false; }
			if (GetAsyncKeyState(VK_RIGHT)) { down = false; left = false; right = true; }
			if (down)
				g::pCmd->viewangles.y -= 180.f;
			if (left)
				g::pCmd->viewangles.y += 90.f;
			if (right)
				g::pCmd->viewangles.y -= 90.f;
			break;
		case 2:
			if (!g::bSendPacket && g::pLocalEntity->AnimState())
				g::pCmd->viewangles.y = g_Math.NormalizeYaw(g::RealAngle.y + 90 + test);
			else
				FreeStanding();
			break;

		}
	};

	antiaim.fakelag();
	pitch();
	real_yaw();

}

c_antiaim antiaim;