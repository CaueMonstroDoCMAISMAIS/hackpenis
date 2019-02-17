#pragma once
#include "Definitions.h"
#include "IClientUnknown.h"
#include "IClientEntityList.h"
#include "..\Utils\Utils.h"
#include "..\Utils\NetvarManager.h"
#include "Studio.h"
#include "IVModelInfoClient.h"
#include "../Utils/Math.h"

// class predefinition
class C_BaseCombatWeapon;

class C_AnimState
{
public:
	char pad[3];
	char bUnknown; //0x4
	char pad2[91];
	void* pBaseEntity; //0x60
	void* pActiveWeapon; //0x64
	void* pLastActiveWeapon; //0x68
	float m_flLastClientSideAnimationUpdateTime; //0x6C
	int m_iLastClientSideAnimationUpdateFramecount; //0x70
	float m_flEyePitch; //0x74
	float m_flEyeYaw; //0x78
	float m_flPitch; //0x7C
	float m_flGoalFeetYaw; //0x80
	float m_flCurrentFeetYaw; //0x84
	float m_flCurrentTorsoYaw; //0x88
	float m_flUnknownVelocityLean; //0x8C //changes when moving/jumping/hitting ground
	float m_flLeanAmount; //0x90
	char pad4[4]; //NaN
	float m_flFeetCycle; //0x98 0 to 1
	float m_flFeetYawRate; //0x9C 0 to 1
	float m_fUnknown2;
	float m_fDuckAmount; //0xA4
	float m_fLandingDuckAdditiveSomething; //0xA8
	float m_fUnknown3; //0xAC
	Vector m_vOrigin; //0xB0, 0xB4, 0xB8
	Vector m_vLastOrigin; //0xBC, 0xC0, 0xC4
	float m_vVelocityX; //0xC8
	float m_vVelocityY; //0xCC
	char pad5[4];
	float m_flUnknownFloat1; //0xD4 Affected by movement and direction
	char pad6[8];
	float m_flUnknownFloat2; //0xE0 //from -1 to 1 when moving and affected by direction
	float m_flUnknownFloat3; //0xE4 //from -1 to 1 when moving and affected by direction
	float m_unknown; //0xE8
	float speed_2d; //0xEC
	float flUpVelocity; //0xF0
	float m_flSpeedNormalized; //0xF4 //from 0 to 1
	float m_flFeetSpeedForwardsOrSideWays; //0xF8 //from 0 to 2. something  is 1 when walking, 2.something when running, 0.653 when crouch walking
	float m_flFeetSpeedUnknownForwardOrSideways; //0xFC //from 0 to 3. something
	float m_flTimeSinceStartedMoving; //0x100
	float m_flTimeSinceStoppedMoving; //0x104
	unsigned char m_bOnGround; //0x108
	unsigned char m_bInHitGroundAnimation; //0x109
	char pad7[10];
	float m_flLastOriginZ; //0x114
	float m_flHeadHeightOrOffsetFromHittingGroundAnimation; //0x118 from 0 to 1, is 1 when standing
	float m_flStopToFullRunningFraction; //0x11C from 0 to 1, doesnt change when walking or crouching, only running
	char pad8[4]; //NaN
	float m_flUnknownFraction; //0x124 affected while jumping and running, or when just jumping, 0 to 1
	char pad9[4]; //NaN
	float m_flUnknown3;
	char pad10[528];
};

class AnimationLayer {
public:
	char  pad_0000[20];
	// These should also be present in the padding, don't see the use for it though
	//float	m_flLayerAnimtime;
	//float	m_flLayerFadeOuttime;
	unsigned int m_nOrder; //0x0014
	unsigned int m_nSequence; //0x0018
	float m_flPrevCycle; //0x001C
	float m_flWeight; //0x0020
	float m_flWeightDeltaRate; //0x0024
	float m_flPlaybackRate; //0x0028
	float m_flCycle; //0x002C
	void *m_pOwner; //0x0030 // player's thisptr
	char  pad_0038[4]; //0x0034
}; //Size: 0x0038

/*void C_BaseEntity::FixSetupBones(matrix3x4_t *Matrix)
{
	int Backup = *(int*)((uintptr_t)this + 0x274);
	*(int*)((uintptr_t)this + 0x274) = 0;
	Vector absOriginBackupLocal = this->GetAbsOrigin();
	this->SetAbsOrigin(this->GetOrigin());
	this->SetupBones(Matrix, 128, 0x00000100, g_pGlobalVars->curtime);
	this->SetAbsOrigin(absOriginBackupLocal);
	*(int*)((uintptr_t)this + 0x274) = Backup;
}

Vector C_BaseEntity::GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix, float *Radius)
{
	studiohdr_t* hdr = g_MdlInfo->GetStudiomodel(this->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

	if (hitbox)
	{
		Vector vMin, vMax, vCenter, sCenter;

		g_Math.VectorTransform_2(hitbox->bbmin, Matrix[hitbox->bone], vMin);
		g_Math.VectorTransform_2(hitbox->bbmax, Matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) * 0.5;

		*Radius = hitbox->m_flRadius;

		return vCenter;
	}

	return Vector(0, 0, 0);
}

Vector C_BaseEntity::GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix) // any public source
{
	studiohdr_t* hdr = g_MdlInfo->GetStudiomodel(this->GetModel());
	mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
	mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

	if (hitbox)
	{
		Vector vMin, vMax, vCenter, sCenter;

		g_Math.VectorTransform_2(hitbox->bbmin, Matrix[hitbox->bone], vMin);
		g_Math.VectorTransform_2(hitbox->bbmax, Matrix[hitbox->bone], vMax);
		vCenter = (vMin + vMax) * 0.5;

		return vCenter;
	}

	return Vector(0, 0, 0);
}

bool C_BaseEntity::IsKnifeorNade()
{
	if (!this)
		return false;
	if (!this->IsAlive())
		return false;

	C_BaseCombatWeapon *pWeapon = (C_BaseCombatWeapon*)this->GetActiveWeapon();

	if (!pWeapon)
		return false;

	std::string WeaponName = pWeapon->GetName();

	if (WeaponName == "weapon_knife")
		return true;
	else if (WeaponName == "weapon_incgrenade")
		return true;
	else if (WeaponName == "weapon_decoy")
		return true;
	else if (WeaponName == "weapon_flashbang")
		return true;
	else if (WeaponName == "weapon_hegrenade")
		return true;
	else if (WeaponName == "weapon_smokegrenade")
		return true;
	else if (WeaponName == "weapon_molotov")
		return true;

	return false;
}

float C_BaseEntity::FireRate()
{
	if (!this)
		return 0.f;
	if (!this->IsAlive())
		return 0.f;
	if (this->IsKnifeorNade())
		return 0.f;

	C_BaseCombatWeapon *pWeapon = (C_BaseCombatWeapon*)this->GetActiveWeapon();

	if (!pWeapon)
		return false;

	std::string WeaponName = pWeapon->GetName();

	if (WeaponName == "weapon_glock")
		return 0.15f;
	else if (WeaponName == "weapon_hkp2000")
		return 0.169f;
	else if (WeaponName == "weapon_p250")//the cz and p250 have the same name idky same with other guns
		return 0.15f;
	else if (WeaponName == "weapon_tec9")
		return 0.12f;
	else if (WeaponName == "weapon_elite")
		return 0.12f;
	else if (WeaponName == "weapon_fiveseven")
		return 0.15f;
	else if (WeaponName == "weapon_deagle")
		return 0.224f;
	else if (WeaponName == "weapon_nova")
		return 0.882f;
	else if (WeaponName == "weapon_sawedoff")
		return 0.845f;
	else if (WeaponName == "weapon_mag7")
		return 0.845f;
	else if (WeaponName == "weapon_xm1014")
		return 0.35f;
	else if (WeaponName == "weapon_mac10")
		return 0.075f;
	else if (WeaponName == "weapon_ump45")
		return 0.089f;
	else if (WeaponName == "weapon_mp9")
		return 0.070f;
	else if (WeaponName == "weapon_bizon")
		return 0.08f;
	else if (WeaponName == "weapon_mp7")
		return 0.08f;
	else if (WeaponName == "weapon_p90")
		return 0.070f;
	else if (WeaponName == "weapon_galilar")
		return 0.089f;
	else if (WeaponName == "weapon_ak47")
		return 0.1f;
	else if (WeaponName == "weapon_sg556")
		return 0.089f;
	else if (WeaponName == "weapon_m4a1")
		return 0.089f;
	else if (WeaponName == "weapon_aug")
		return 0.089f;
	else if (WeaponName == "weapon_m249")
		return 0.08f;
	else if (WeaponName == "weapon_negev")
		return 0.0008f;
	else if (WeaponName == "weapon_ssg08")
		return 1.25f;
	else if (WeaponName == "weapon_awp")
		return 1.463f;
	else if (WeaponName == "weapon_g3sg1")
		return 0.25f;
	else if (WeaponName == "weapon_scar20")
		return 0.25f;
	else if (WeaponName == "weapon_mp5sd")
		return 0.08f;
	else
		return .0f;

}*/

class C_BaseEntity : public IClientUnknown, public IClientRenderable, public IClientNetworkable
{
private:
	template <typename T>
	T& read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data)
	{
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}

public:
	NETVAR("DT_CSPlayer", "m_iHealth", GetHealth, int);
	NETVAR("DT_CSPlayer", "m_fFlags", GetFlags, int);
	NETVAR("DT_CSPlayer", "m_iTeamNum", GetTeam, int);
	NETVAR("DT_BaseEntity", "m_vecMins", GetOBBMins, Vector);
	NETVAR("DT_BaseEntity", "m_vecMaxs", GetOBBMaxs, Vector);
	NETVAR("DT_CSPlayer", "m_angEyeAngles", GetEyeAngles, Vector);
	NETVAR("DT_CSPlayer", "m_flLowerBodyYawTarget", GetLowerBodyYaw, float);
	NETVAR("DT_BaseAnimating", "m_flCycle", GetCycle, float);
	NETVAR("DT_BaseAnimating", "m_nSequence", GetSequence, int);
	NETVAR("DT_CSPlayer", "m_flSimulationTime", GetSimulationTime, float);
	NETVAR("DT_BasePlayer", "m_vecOrigin", GetVecOrigin, Vector);
	NETVAR("DT_BasePlayer", "m_vecVelocity[0]", GetVelocity, Vector);
	NETVAR("DT_CSPlayer", "m_ArmorValue", GetArmor, int);
	NETVAR("DT_CSPlayer", "m_bHasHelmet", HasHelmet, bool);
	NETVAR("DT_CSPlayer", "m_nTickBase", GetTickBase, int);
	NETVAR("DT_CSPlayer", "m_bGunGameImmunity", GetIsSpawnProtected, bool);
	NETVAR("DT_CSPlayer", "m_bIsScoped", GetScoped, bool);
	NETVAR("DT_CSPlayer", "m_nMoveType", GetMoveType, int);
	NETVAR("DT_CSPlayer", "m_iAccount", GetBalance, int);
	NETVAR("DT_BasePlayer", "m_vecViewOffset[0]", GetViewOffset, Vector);
	NETVAR("DT_BaseViewModel", "m_hOwner", GetOwnerHandle, HANDLE);
	NETVAR("DT_CSPlayer", "m_bIsPlayerGhost", GetIsPlayerGhost, bool);
	NETVAR("DT_BasePlayer", "m_aimPunchAngle", GetAimPunch, Vector);
	NETVAR("DT_BasePlayer", "m_viewPunchAngle", GetViewPunch, Vector);
	NETVAR("DT_BasePlayer", "m_nHitboxSet", GetGitboxSet, int);
	NETVAR("DT_CSPlayer", "m_flDuckAmount", GetCrouchAmount, float);
	NETVAR("DT_CSPlayer", "m_flNextAttack", GetNextAttack, float);
	NETVAR("DT_SmokeGrenadeProjectile", "m_nSmokeEffectTickBegin", GetGrenadeSmokeTickBegin, int);
	NETVAR("DT_HEGrenade", "m_flDamage", GetHeDamage, float);
	NETVAR("DT_CSPlayer", "m_iShotsFired", GetShotsFired, int);
	NETVAR("DT_CSPlayer", "m_flFlashDuration", SetFlashDuration, float);
	NETVAR("DT_CSPlayer", "m_iFlashMaxAlpha", SetFlashAlpha, int);
	NETVAR("DT_CSPlayer", "m_iObserverMode", SetObserverMode, int);
	NETVAR("DT_CSPlayer", "m_lifeState", GetLifeState, int);
	NETVAR("DT_BaseEntity", "m_nFallbackPaintKit", fallbackPaintKit, int);
	NETVAR("DT_CSPlayer", "m_bIsDefusing", isDefusing, bool);
	NETVAR("DT_CSPlayer", "m_bHasDefuser", hasDefuser, bool);
	NETVAR("DT_PlantedC4", "m_flC4Blow", GetC4Blow, float);
	NETVAR("DT_PlantedC4", "m_flDefuseCountDown", GetDefuseCountDown, int);
	NETVAR("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", GetItemDefinitionIndex, int);

	WeaponInfo_t* GetCSWpnData()
	{
		return Utils::CallVTable< WeaponInfo_t*(__thiscall*)(void*) >(this, 448)(this);
	}

	std::string GetName()
	{
		///TODO: Test if szWeaponName returns proper value for m4a4 / m4a1-s or it doesnt recognize them.
		return std::string(this->GetCSWpnData()->szWeaponName);
	}

	void C_BaseEntity::FixSetupBones(matrix3x4_t *Matrix)
	{
		int Backup = *(int*)((uintptr_t)this + 0x274);
		*(int*)((uintptr_t)this + 0x274) = 0;
		Vector absOriginBackupLocal = this->GetAbsOrigin();
		this->SetOrigin(this->GetOrigin());
		this->SetupBones(Matrix, 128, 0x00000100, g_pGlobalVars->curtime);
		this->SetAngles(absOriginBackupLocal);
		*(int*)((uintptr_t)this + 0x274) = Backup;
	}

	Vector C_BaseEntity::GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix, float *Radius)
	{
		studiohdr_t* hdr = g_MdlInfo->GetStudiomodel(this->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
		mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

		if (hitbox)
		{
			Vector vMin, vMax, vCenter, sCenter;

			g_Math.VectorTransform_2(hitbox->bbmin, Matrix[hitbox->bone], vMin);
			g_Math.VectorTransform_2(hitbox->bbmax, Matrix[hitbox->bone], vMax);
			vCenter = (vMin + vMax) * 0.5;

			*Radius = hitbox->m_flRadius;

			return vCenter;
		}

		return Vector(0, 0, 0);
	}

	Vector C_BaseEntity::GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix) // any public source
	{
		studiohdr_t* hdr = g_MdlInfo->GetStudiomodel(this->GetModel());
		mstudiohitboxset_t* set = hdr->GetHitboxSet(0);
		mstudiobbox_t* hitbox = set->GetHitbox(Hitbox);

		if (hitbox)
		{
			Vector vMin, vMax, vCenter, sCenter;

			g_Math.VectorTransform_2(hitbox->bbmin, Matrix[hitbox->bone], vMin);
			g_Math.VectorTransform_2(hitbox->bbmax, Matrix[hitbox->bone], vMax);
			vCenter = (vMin + vMax) * 0.5;

			return vCenter;
		}

		return Vector(0, 0, 0);
	}

	bool C_BaseEntity::IsKnifeorNade()
	{
		if (!this)
			return false;
		if (!this->IsAlive())
			return false;

		C_BaseEntity* pWeapon = (C_BaseEntity*)this->GetActiveWeapon();

		if (!pWeapon)
			return false;

		std::string WeaponName = pWeapon->GetName();

		if (WeaponName == "weapon_incgrenade")
			return true;
		else if (WeaponName == "weapon_decoy")
			return true;
		else if (WeaponName == "weapon_flashbang")
			return true;
		else if (WeaponName == "weapon_hegrenade")
			return true;
		else if (WeaponName == "weapon_smokegrenade")
			return true;
		else if (WeaponName == "weapon_molotov")
			return true;

		return false;
	}

	float C_BaseEntity::FireRate()
	{
		if (!this)
			return 0.f;
		if (!this->IsAlive())
			return 0.f;
		if (this->IsKnifeorNade())
			return 0.f;

		C_BaseEntity* pWeapon = (C_BaseEntity*)this->GetActiveWeapon();

		if (!pWeapon)
			return false;

		std::string WeaponName = pWeapon->GetName();

		if (WeaponName == "weapon_glock")
			return 0.15f;
		else if (WeaponName == "weapon_hkp2000")
			return 0.169f;
		else if (WeaponName == "weapon_p250")//the cz and p250 have the same name idky same with other guns
			return 0.15f;
		else if (WeaponName == "weapon_tec9")
			return 0.12f;
		else if (WeaponName == "weapon_elite")
			return 0.12f;
		else if (WeaponName == "weapon_fiveseven")
			return 0.15f;
		else if (WeaponName == "weapon_deagle")
			return 0.224f;
		else if (WeaponName == "weapon_nova")
			return 0.882f;
		else if (WeaponName == "weapon_sawedoff")
			return 0.845f;
		else if (WeaponName == "weapon_mag7")
			return 0.845f;
		else if (WeaponName == "weapon_xm1014")
			return 0.35f;
		else if (WeaponName == "weapon_mac10")
			return 0.075f;
		else if (WeaponName == "weapon_ump45")
			return 0.089f;
		else if (WeaponName == "weapon_mp9")
			return 0.070f;
		else if (WeaponName == "weapon_bizon")
			return 0.08f;
		else if (WeaponName == "weapon_mp7")
			return 0.08f;
		else if (WeaponName == "weapon_p90")
			return 0.070f;
		else if (WeaponName == "weapon_galilar")
			return 0.089f;
		else if (WeaponName == "weapon_ak47")
			return 0.1f;
		else if (WeaponName == "weapon_sg556")
			return 0.089f;
		else if (WeaponName == "weapon_m4a1")
			return 0.089f;
		else if (WeaponName == "weapon_aug")
			return 0.089f;
		else if (WeaponName == "weapon_m249")
			return 0.08f;
		else if (WeaponName == "weapon_negev")
			return 0.0008f;
		else if (WeaponName == "weapon_ssg08")
			return 1.25f;
		else if (WeaponName == "weapon_awp")
			return 1.463f;
		else if (WeaponName == "weapon_g3sg1")
			return 0.25f;
		else if (WeaponName == "weapon_scar20")
			return 0.25f;
		else if (WeaponName == "weapon_mp5sd")
			return 0.08f;
		else
			return .0f;

	}

	PlayerInfo_t GetPlayerInfo()
	{
		PlayerInfo_t info;
		g_pEngine->GetPlayerInfo(EntIndex(), &info);

		return info;
	}

	C_BaseCombatWeapon* GetMyWeapons()
	{
		auto get_weapons = read<DWORD>(sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_hMyWeapons"))) & 0xFFF;
		return reinterpret_cast<C_BaseCombatWeapon*>(g_pEntityList->GetClientEntity(get_weapons));
	}

	C_BaseCombatWeapon* GetActiveWeapon()
	{
		auto active_weapon = read<DWORD>(sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_hActiveWeapon"))) & 0xFFF;
		return reinterpret_cast<C_BaseCombatWeapon*>(g_pEntityList->GetClientEntity(active_weapon));
	}

	Vector& GetAbsOrigin()
	{
		return Utils::CallVTable<Vector&(__thiscall*)(void*)>(this, 10)(this);
	}

	int ArmorValue()
	{
		static auto m_ArmorValue = sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_ArmorValue"));
		return read<int>(m_ArmorValue);
	}

	C_AnimState *AnimState()
	{
		return *reinterpret_cast<C_AnimState**>(uintptr_t(this) + 0x3900);
	}

	int C_BaseEntity::GetIndex()
	{
		return *reinterpret_cast<int*>((uintptr_t)this + 0x64);
	}

	void C_BaseEntity::SetOrigin(Vector origin)
	{
		using SetAbsOriginFn = void(__thiscall*)(void*, const Vector &origin);
		static SetAbsOriginFn SetAbsOrigin = (SetAbsOriginFn)Utils::FindSignature("client_panorama.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8");
	
		SetAbsOrigin(this, origin);
	}

	void C_BaseEntity::SetAngles(const Vector &angles)
	{
		using SetAbsAnglesFn = void(__thiscall*)(void*, const Vector &angles);
		static SetAbsAnglesFn SetAbsAngles = (SetAbsAnglesFn)Utils::FindSignature("client_panorama.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8");

		SetAbsAngles(this, angles);
	}

	bool IsAlive()
	{
		return this->GetHealth() > 0;
	}

	Vector GetEyePosition()
	{
		return this->GetVecOrigin() + this->GetViewOffset();
	}

	Vector GetOrigin()
	{
		static auto m_vecOrigin = sdk::util::getNetVar(sdk::util::fnv::hash("DT_BaseEntity"), sdk::util::fnv::hash("m_vecOrigin"));
		return read<Vector>(m_vecOrigin);
	}

	matrix3x4_t& get_rgflcoordinateframe()
	{
		static auto _m_rgflCoordinateFrame = sdk::util::getNetVar(sdk::util::fnv::hash("DT_CSPlayer"), sdk::util::fnv::hash("m_CollisionGroup")) - 0x30;
		return *reinterpret_cast<matrix3x4_t*>(reinterpret_cast<uintptr_t>(this) + _m_rgflCoordinateFrame);
	}

	Vector GetBonePos(int i)
	{
		matrix3x4_t boneMatrix[128];
		if (this->SetupBones(boneMatrix, 128, BONE_USED_BY_HITBOX, static_cast<float>(GetTickCount64())))
		{
			return Vector(boneMatrix[i][0][3], boneMatrix[i][1][3], boneMatrix[i][2][3]);
		}
		return Vector(0, 0, 0);
	}

	Vector GetAimPunchAngle()
	{
		return *reinterpret_cast<Vector*>(uintptr_t(this) + uintptr_t(0x302C));
	}

	//Vector GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix, float *Radius);
	//Vector GetHitboxPosition(int Hitbox, matrix3x4_t *Matrix);
	//void FixSetupBones(matrix3x4_t *Matrix);
	//void SetAbsAngles(Vector angles);
	//void SetAbsOrigin(Vector origin);
	/*bool IsKnifeorNade();
	float FireRate();*/
};

class C_BaseCombatWeapon : public C_BaseEntity
{
private:
	template <typename T>
	T& read(uintptr_t offset)
	{
		return *reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset);
	}

	template <typename T>
	void write(uintptr_t offset, T data)
	{
		*reinterpret_cast<T*>(reinterpret_cast<uintptr_t>(this) + offset) = data;
	}
public:
	NETVAR("DT_BaseCombatWeapon", "m_iItemDefinitionIndex", GetItemDefinitionIndex, short);
	NETVAR("DT_BaseCombatWeapon", "m_flNextPrimaryAttack", GetNextPrimaryAttack, float);
	NETVAR("DT_BaseCombatWeapon", "m_iClip1", GetAmmo, int);

	WeaponInfo_t* GetCSWpnData()
	{
		return Utils::CallVTable< WeaponInfo_t*(__thiscall*)(void*) >(this, 448)(this);
	}

	float GetInaccuracy()
	{
		typedef float(__thiscall* oInaccuracy)(PVOID);
		return Utils::CallVTable< oInaccuracy >(this, 471)(this);
	}

	float GetSpread()
	{
		typedef float(__thiscall* oWeaponSpread)(PVOID);
		return Utils::CallVTable< oWeaponSpread >(this, 439)(this);
	}

	float GetAccuracyPenalty()
	{
		static auto m_fAccuracyPenalty = sdk::util::getNetVar(sdk::util::fnv::hash("DT_WeaponCSBase"), sdk::util::fnv::hash("m_fAccuracyPenalty"));
		return read<float>(m_fAccuracyPenalty);
	}

	float GetLastShotTime()
	{
		static auto m_fLastShotTime = sdk::util::getNetVar(sdk::util::fnv::hash("DT_WeaponCSBase"), sdk::util::fnv::hash("m_fLastShotTime"));
		return read<float>(m_fLastShotTime);
	}

	void AccuracyPenalty()
	{
		typedef void(__thiscall *OrigFn)(void *);
		return Utils::CallVTable<OrigFn>(this, 472)(this);
	}

	bool realWeapon()
	{
		short idx = GetItemDefinitionIndex();

		return (idx == WEAPON_C4 || idx == WEAPON_KNIFE || idx == WEAPON_KNIFE_BAYONET || idx == WEAPON_KNIFE_BUTTERFLY || idx == WEAPON_KNIFE_FALCHION
			|| idx == WEAPON_KNIFE_FLIP || idx == WEAPON_KNIFE_GUT || idx == WEAPON_KNIFE_KARAMBIT || idx == WEAPON_KNIFE_M9_BAYONET || idx == WEAPON_KNIFE_PUSH
			|| idx == WEAPON_KNIFE_SURVIVAL_BOWIE || idx == WEAPON_KNIFE_T || idx == WEAPON_KNIFE_TACTICAL || idx == WEAPON_FLASHBANG || idx == WEAPON_HEGRENADE
			|| idx == WEAPON_SMOKEGRENADE || idx == WEAPON_MOLOTOV || idx == WEAPON_DECOY || idx == WEAPON_INCGRENADE || idx == WEAPON_TAGRENADE || idx == WEAPON_FISTS
			|| idx == WEAPON_HEALTHSHOT || idx == WEAPON_BREACHCHARGE || idx == WEAPON_TABLET || idx == WEAPON_MELEE || idx == WEAPON_AXE || idx == WEAPON_HAMMER
			|| idx == WEAPON_SPANNER || idx == WEAPON_KNIFE_GHOST || idx == WEAPON_FIREBOMB || idx == WEAPON_DIVERSION || idx == WEAPON_FRAG_GRENADE || idx == WEAPON_KNIFE_URSUS
			|| idx == WEAPON_KNIFE_GYPSY_JACKKNIFE || idx == WEAPON_KNIFE_STILETTO || idx == WEAPON_KNIFE_WIDOWMAKER);
	}

	char * getIcon()
	{
		switch (GetItemDefinitionIndex())
		{
		case WEAPON_KNIFE_BAYONET:
			return "1";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "7";
		case WEAPON_KNIFE_BUTTERFLY:
			return "8";
		case WEAPON_KNIFE:
			return "]";
		case WEAPON_KNIFE_FALCHION:
			return "0";
		case WEAPON_KNIFE_FLIP:
			return "2";
		case WEAPON_KNIFE_GUT:
			return "3";
		case WEAPON_KNIFE_KARAMBIT:
			return "4";
		case WEAPON_KNIFE_M9_BAYONET:
			return "5";
		case WEAPON_KNIFE_T:
			return "[";
		case WEAPON_KNIFE_TACTICAL:
			return "6";
		case WEAPON_KNIFE_PUSH:
			return "]";
		case WEAPON_DEAGLE:
			return "A";
		case WEAPON_ELITE:
			return "B";
		case WEAPON_FIVESEVEN:
			return "C";
		case WEAPON_GLOCK:
			return "D";
		case WEAPON_HKP2000:
			return "E";
		case WEAPON_P250:
			return "F";
		case WEAPON_USP_SILENCER:
			return "G";
		case WEAPON_TEC9:
			return "H";
		case WEAPON_REVOLVER:
			return "J";
		case WEAPON_MAC10:
			return "K";
		case WEAPON_UMP45:
			return "L";
		case WEAPON_BIZON:
			return "M";
		case WEAPON_MP7:
			return "N";
		case WEAPON_MP9:
			return "O";
		case WEAPON_P90:
			return "P";
		case WEAPON_GALILAR:
			return "Q";
		case WEAPON_FAMAS:
			return "R";
		case WEAPON_M4A1_SILENCER:
			return "S";
		case WEAPON_M4A1:
			return "T";
		case WEAPON_AUG:
			return "U";
		case WEAPON_SG556:
			return "V";
		case WEAPON_AK47:
			return "W";
		case WEAPON_G3SG1:
			return "X";
		case WEAPON_SCAR20:
			return "Y";
		case WEAPON_AWP:
			return "Z";
		case WEAPON_SSG08:
			return "a";
		case WEAPON_XM1014:
			return "b";
		case WEAPON_SAWEDOFF:
			return "c";
		case WEAPON_MAG7:
			return "d";
		case WEAPON_NOVA:
			return "e";
		case WEAPON_NEGEV:
			return "f";
		case WEAPON_M249:
			return "g";
		case WEAPON_TASER:
			return "h";
		case WEAPON_FLASHBANG:
			return "i";
		case WEAPON_HEGRENADE:
			return "j";
		case WEAPON_SMOKEGRENADE:
			return "k";
		case WEAPON_MOLOTOV:
			return "l";
		case WEAPON_DECOY:
			return "m";
		case WEAPON_INCGRENADE:
			return "n";
		case WEAPON_C4:
			return "o";
		case WEAPON_CZ75A:
			return "I";
		case WEAPON_KNIFE_URSUS:
			return "]";
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return "]";
		case WEAPON_KNIFE_STILETTO:
			return "]";
		case WEAPON_KNIFE_WIDOWMAKER:
			return "]";
		default:
			return "  ";
		}
	}

	char * getNameLowerCase()
	{
		switch (GetItemDefinitionIndex())
		{
		case WEAPON_KNIFE_BAYONET:
			return "bayonet";
		case WEAPON_KNIFE_SURVIVAL_BOWIE:
			return "bowie";
		case WEAPON_KNIFE_BUTTERFLY:
			return "butterfly";
		case WEAPON_KNIFE:
			return "knife";
		case WEAPON_KNIFE_FALCHION:
			return "falchion";
		case WEAPON_KNIFE_FLIP:
			return "flip";
		case WEAPON_KNIFE_GUT:
			return "gut";
		case WEAPON_KNIFE_KARAMBIT:
			return "karambit";
		case WEAPON_KNIFE_M9_BAYONET:
			return "m9 bayonet";
		case WEAPON_KNIFE_T:
			return "knife";
		case WEAPON_KNIFE_TACTICAL:
			return "huntsman";
		case WEAPON_KNIFE_PUSH:
			return "daggers";
		case WEAPON_DEAGLE:
			return "desert eagle";
		case WEAPON_ELITE:
			return "berretas";
		case WEAPON_FIVESEVEN:
			return "fiveseven";
		case WEAPON_GLOCK:
			return "glock";
		case WEAPON_HKP2000:
			return "p2000";
		case WEAPON_P250:
			return "p250";
		case WEAPON_USP_SILENCER:
			return "usp-s";
		case WEAPON_TEC9:
			return "tec9";
		case WEAPON_REVOLVER:
			return "revolver";
		case WEAPON_MAC10:
			return "mac10";
		case WEAPON_UMP45:
			return "ump45";
		case WEAPON_BIZON:
			return "bizon";
		case WEAPON_MP7:
			return "mp7";
		case WEAPON_MP5:
			return "mp5";
		case WEAPON_MP9:
			return "mp9";
		case WEAPON_P90:
			return "p90";
		case WEAPON_GALILAR:
			return "galil";
		case WEAPON_FAMAS:
			return "famas";
		case WEAPON_M4A1_SILENCER:
			return "m4a1-s";
		case WEAPON_M4A1:
			return "m4a4";
		case WEAPON_AUG:
			return "aug";
		case WEAPON_SG556:
			return "sg556";
		case WEAPON_AK47:
			return "ak47";
		case WEAPON_G3SG1:
			return "g3sg1";
		case WEAPON_SCAR20:
			return "scar20";
		case WEAPON_AWP:
			return "awp";
		case WEAPON_SSG08:
			return "scout";
		case WEAPON_XM1014:
			return "xm1014";
		case WEAPON_SAWEDOFF:
			return "sawedoff";
		case WEAPON_MAG7:
			return "mag7";
		case WEAPON_NOVA:
			return "nova";
		case WEAPON_NEGEV:
			return "negev";
		case WEAPON_M249:
			return "m249";
		case WEAPON_TASER:
			return "zeus";
		case WEAPON_FLASHBANG:
			return "flashbang";
		case WEAPON_HEGRENADE:
			return "grenade";
		case WEAPON_SMOKEGRENADE:
			return "smoke";
		case WEAPON_MOLOTOV:
			return "molotov";
		case WEAPON_DECOY:
			return "decoy";
		case WEAPON_INCGRENADE:
			return "incendiary";
		case WEAPON_C4:
			return "bomb";
		case WEAPON_CZ75A:
			return "cz75a";
		case WEAPON_KNIFE_URSUS:
			return "ursus";
		case WEAPON_KNIFE_GYPSY_JACKKNIFE:
			return "navaja";
		case WEAPON_KNIFE_STILETTO:
			return "stiletto";
		case WEAPON_KNIFE_WIDOWMAKER:
			return "talon";
		case WEAPON_TAGRENADE:
			return "tactical awareness nade";
		case WEAPON_HEALTHSHOT:
			return "health shot";
		case WEAPON_FISTS:
			return "fists";
		case WEAPON_BREACHCHARGE:
			return "breach charge";
		case WEAPON_TABLET:
			return "tablet";
		case WEAPON_MELEE:
			return "knife";
		case WEAPON_AXE:
			return "axe";
		case WEAPON_HAMMER:
			return "hammer";
		case WEAPON_SPANNER:
			return "wrench";
		case WEAPON_KNIFE_GHOST:
			return "ghost knife";
		case WEAPON_FIREBOMB:
			return "fire bomb";
		case WEAPON_DIVERSION:
			return "diversion";
		case WEAPON_FRAG_GRENADE:
			return "frag";
		default:
			return "error";
		}
	}
	std::string GetName()
	{
		///TODO: Test if szWeaponName returns proper value for m4a4 / m4a1-s or it doesnt recognize them.
		return std::string(this->GetCSWpnData()->szWeaponName);
	}
};

