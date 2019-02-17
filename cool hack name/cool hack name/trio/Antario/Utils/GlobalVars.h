#pragma once
#include "..\SDK\CInput.h"
#include "..\SDK\CEntity.h"

namespace g
{
	extern bool		      fakelag;
	extern bool           bSendPacket;
    extern CUserCmd*      pCmd;
    extern C_BaseEntity*  pLocalEntity;
	extern C_BaseCombatWeapon*  pLocalEntity2;
    extern std::uintptr_t uRandomSeed;
	using msg_t = void(__cdecl*)(const char*, ...);
	extern msg_t		  pMsg;
	extern int            TargetIndex;
	extern Vector         EnemyEyeAngs[65];
	extern Vector         AimbotHitbox[65][28];
	extern Vector         RealAngle;
	extern Vector         FakeAngle;
	extern bool           Shot[65];
	extern bool           Hit[65];
	extern int            MissedShots[65];
}
