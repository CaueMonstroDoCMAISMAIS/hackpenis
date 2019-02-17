#pragma once
#include "../SDK/Vector.h"
#include "../SDK/VMatrix.h"
#include "../Utils/SPoint.h"
#include <array>
#define PI 3.14159265358979323846f

class Math
{
public:
	static Vector VectorTransform(Vector vector, matrix3x4_t matrix);
	static void VectorTransform_2(const Vector & in1, const matrix3x4_t & in2, Vector & out);

	void RotateTriangle(std::array<Vector2D, 3>& points, float rotation);

	void VectorAngles_2(const Vector & forward, Vector & angles);

	void AngleVectors(const Vector& angles, Vector* forward = nullptr, Vector* right = nullptr, Vector* up = nullptr);

	void VectorAngles_3(const Vector& forward, Vector& up, Vector& angles);

	float DistanceTo(Vector vecDst, Vector vecSrc);

	float RandomFloat(float min, float max);

	Vector NormalizeAngle(Vector angle);

	float NormalizeYaw(float yaw);

	float Distance(Vector2D point1, Vector2D point2);

	Vector CalcAngle(Vector src, Vector dst);

	Vector ClampAngles(Vector& angles);

	float GRD_TO_BOG(float GRD);

	void CalcAngle(Vector src, Vector dst, Vector & angles);

	static constexpr float Math::rad_2_deg(float radian)
	{
		return radian * (180.f / PI);
	}

	static constexpr float Math::deg_2_rad(float degree)
	{
		return degree * (PI / 180.f);
	}
};

extern Math g_Math;
