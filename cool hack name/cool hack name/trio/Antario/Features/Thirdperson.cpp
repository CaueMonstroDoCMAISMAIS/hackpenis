#include "Thirdperson.h"

/* thirdperson */
thirdperson g_thirdperson;

void thirdperson::doThirdperson()
{
	/* return if local is nullptr */
	if (g::pLocalEntity == nullptr)
		return;

	/* check if we are connected */
	if (!g_pEngine->IsConnected() && !g_pEngine->IsInGame())
		return;

	/* vec angles */
	static Vector vecAngles;

	/* pointer to localplayer */
	C_BaseEntity* localplayer = g_pEntityList->GetClientEntity(g_pEngine->GetLocalPlayer());

	/* get view angles */
	g_pEngine->GetViewAngles(vecAngles);

	/* keybind (if key pressed, make bool true) */
	if (g::pLocalEntity->IsAlive())
		Keybind(g_Settings.visuals.btThirdperonKeybind, g_Settings.visuals.iThirdpersonKeybind, bThirdperson);

	if (g_Settings.visuals.bSpecThirdperson && !g::pLocalEntity->IsAlive())
	{
		g::pLocalEntity->SetObserverMode() = 5;
	}

	/* if we have clicked the key */
	if (bThirdperson && g::pLocalEntity->IsAlive())
	{
		/* if we are not in thirdperson */
		if (!g_pInput->m_fCameraInThirdPerson)
		{
			/* getting correct distance */
			auto GetCorrectDistance = [&localplayer](float ideal_distance) -> float
			{
				/* vector for the inverse angles */
				Vector inverseAngles;
				g_pEngine->GetViewAngles(inverseAngles);

				/* inverse angles by 180 */
				inverseAngles.x *= -1.f, inverseAngles.y += 180.f;

				/* vector for direction */
				Vector direction;
				g_Math.AngleVectors(inverseAngles, &direction);

				/* ray, trace & filters */
				Ray_t ray;
				trace_t trace;
				CTraceFilterEntitiesOnly filter;

				/* dont trace local player */
				filter.pSkip = g::pLocalEntity;

				/* create ray */
				ray.Init(localplayer->GetVecOrigin() + localplayer->GetViewOffset(), (localplayer->GetVecOrigin() + localplayer->GetViewOffset()) + (direction * ideal_distance));

				/* trace ray */
				g_pEngineTrace->TraceRay(ray, MASK_SHOT, &filter, &trace);
				
				/* return the ideal distance */
				return (ideal_distance * trace.fraction) - 10.f;
			};

			/* change the distance from player to camera */
			vecAngles.z = GetCorrectDistance(g_Settings.visuals.iThirdpersonDistance);

			/* make player thirdperson */
			g_pInput->m_fCameraInThirdPerson = true;

			/* set camera view */
			g_pInput->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, vecAngles.z);
		}
	}
	else
	{
		/* set player to firstperson */
		g_pInput->m_fCameraInThirdPerson = false;

		/* return to default view */
		g_pInput->m_vecCameraOffset = Vector(vecAngles.x, vecAngles.y, 0);
	}
}