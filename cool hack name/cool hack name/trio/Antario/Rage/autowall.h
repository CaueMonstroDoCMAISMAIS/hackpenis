#pragma once
#include "..\Utils\GlobalVars.h"
#include "..\SDK\CGlobalVarsBase.h"
#include "..\SDK\IEngineTrace.h"


struct FireBulletData
{
	FireBulletData(const Vector &eyePos, C_BaseEntity* entity) : src(eyePos), filter(entity)
	{
	}

	Vector          src;
	CGameTrace      enter_trace;
	Vector          direction;
	CTraceFilter    filter;
	float           trace_length;
	float           trace_length_remaining;
	float           current_damage;
	int             penetrate_count;
};

class Autowall
{
public:
	bool CanHitFloatingPoint(const Vector &point, const Vector &source);
	float Damage(const Vector &point);
private:
};
extern Autowall g_Autowall;