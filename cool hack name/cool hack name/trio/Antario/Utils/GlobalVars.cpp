#include "GlobalVars.h"

namespace g
{
	bool		   fakelag = false;
	bool           bSendPacket = false;
    CUserCmd*      pCmd         = nullptr;
    C_BaseEntity*  pLocalEntity = nullptr;
	C_BaseCombatWeapon*  pLocalEntity2 = nullptr;
    std::uintptr_t uRandomSeed  = NULL;
	using msg_t = void(__cdecl*)(const char*, ...);
	msg_t		   pMsg = reinterpret_cast< msg_t >(GetProcAddress(GetModuleHandleA("tier0.dll"), "Msg"));
	int            TargetIndex = -1;
	bool           Shot[65];
	bool           Hit[65];
	int            MissedShots[65];
	Vector         EnemyEyeAngs[65];
	Vector         AimbotHitbox[65][28];
	Vector         RealAngle;
	Vector         FakeAngle;
}