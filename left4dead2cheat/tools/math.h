#pragma once
#include "..\sdk\math\vector.h"
#include "..\sdk\math\matrix.h"
#include <math.h>
#include <algorithm>
#define PI 3.14159265358979323846f

namespace Math
{

	template<class T, class U>
	T clamp(T in, U low, U high);

	static vec_t Normalize_y(vec_t ang);
	void SinCos(float a, float* s, float* c);
	void VectorAngle(const Vector& angles, Vector& forward, Vector& right, Vector& up);
	float WorldDistance(const Vector& vecStart, const Vector& vecEnd);
	void AngleVectors(const Vector& angles, Vector& forward);
	void VectorAngles(const Vector& forward, Vector& angles);
	void AngleVectors(const Vector& angles, Vector* forward, Vector* right, Vector* up);
	float AngleDistance(const Vector& vecStart, const Vector& vecEnd, const float& fDistance);
	float NormalizeAngle(const float& fAxis);
	float NormalizeVector(Vector& vec);
	float DotProduct(const Vector& a, const Vector& b);
	float ToRadians(float degrees);
	float ToDegrees(float radians);
	void VectorTransform(const Vector in1, const matrix3x4_t& in2, Vector& out);
	void clamp_angles(Vector& angle);
	void correct_movement(QAngle& wish_angle, cusercmd* m_pcmd);
	Vector VectorAngles(const Vector& vecDirection);
	Vector GetBoneAngles(const Vector& BonePos, const Vector& LocalEyeAngles);
}



static vec_t Math::Normalize_y(vec_t ang)
{
	while (ang < -180.0f)
		ang += 360.0f;
	while (ang > 180.0f)
		ang -= 360.0f;
	return ang;
}
template<class T, class U>
T Math::clamp(T in, U low, U high)
{
	if (in <= low)
		return low;

	if (in >= high)
		return high;

	return in;
}

inline void Math::clamp_angles(Vector& angle)
{
	angle.x = std::clamp(angle.x, -89.f, 89.f);
	angle.y = std::remainderf(angle.y, 360.f);
}

inline void Math::correct_movement(QAngle& wish_angle, cusercmd* m_pcmd)
{

	Vector view_fwd, view_right, view_up, cmd_fwd, cmd_right, cmd_up;
	auto viewangles = m_pcmd->viewangles;
	viewangles.Normalize();

	AngleVectors(wish_angle, &view_fwd, &view_right, &view_up);
	AngleVectors(viewangles, &cmd_fwd, &cmd_right, &cmd_up);

	float v8 = sqrtf((view_fwd.x * view_fwd.x) + (view_fwd.y * view_fwd.y));
	float v10 = sqrtf((view_right.x * view_right.x) + (view_right.y * view_right.y));
	float v12 = sqrtf(view_up.z * view_up.z);

	Vector norm_view_fwd((1.f / v8) * view_fwd.x, (1.f / v8) * view_fwd.y, 0.f);
	Vector norm_view_right((1.f / v10) * view_right.x, (1.f / v10) * view_right.y, 0.f);
	Vector norm_view_up(0.f, 0.f, (1.f / v12) * view_up.z);

	float v14 = sqrtf((cmd_fwd.x * cmd_fwd.x) + (cmd_fwd.y * cmd_fwd.y));
	float v16 = sqrtf((cmd_right.x * cmd_right.x) + (cmd_right.y * cmd_right.y));
	float v18 = sqrtf(cmd_up.z * cmd_up.z);

	Vector norm_cmd_fwd((1.f / v14) * cmd_fwd.x, (1.f / v14) * cmd_fwd.y, 0.f);
	Vector norm_cmd_right((1.f / v16) * cmd_right.x, (1.f / v16) * cmd_right.y, 0.f);
	Vector norm_cmd_up(0.f, 0.f, (1.f / v18) * cmd_up.z);

	float v22 = norm_view_fwd.x * m_pcmd->forwardmove;
	float v26 = norm_view_fwd.y * m_pcmd->forwardmove;
	float v28 = norm_view_fwd.z * m_pcmd->forwardmove;
	float v24 = norm_view_right.x * m_pcmd->sidemove;
	float v23 = norm_view_right.y * m_pcmd->sidemove;
	float v25 = norm_view_right.z * m_pcmd->sidemove;
	float v30 = norm_view_up.x * m_pcmd->upmove;
	float v27 = norm_view_up.z * m_pcmd->upmove;
	float v29 = norm_view_up.y * m_pcmd->upmove;

	m_pcmd->forwardmove = ((((norm_cmd_fwd.x * v24) + (norm_cmd_fwd.y * v23)) + (norm_cmd_fwd.z * v25))
		+ (((norm_cmd_fwd.x * v22) + (norm_cmd_fwd.y * v26)) + (norm_cmd_fwd.z * v28)))
		+ (((norm_cmd_fwd.y * v30) + (norm_cmd_fwd.x * v29)) + (norm_cmd_fwd.z * v27));
	m_pcmd->sidemove = ((((norm_cmd_right.x * v24) + (norm_cmd_right.y * v23)) + (norm_cmd_right.z * v25))
		+ (((norm_cmd_right.x * v22) + (norm_cmd_right.y * v26)) + (norm_cmd_right.z * v28)))
		+ (((norm_cmd_right.x * v29) + (norm_cmd_right.y * v30)) + (norm_cmd_right.z * v27));
	m_pcmd->upmove = ((((norm_cmd_up.x * v23) + (norm_cmd_up.y * v24)) + (norm_cmd_up.z * v25))
		+ (((norm_cmd_up.x * v26) + (norm_cmd_up.y * v22)) + (norm_cmd_up.z * v28)))
		+ (((norm_cmd_up.x * v30) + (norm_cmd_up.y * v29)) + (norm_cmd_up.z * v27));

	m_pcmd->forwardmove = clamp(m_pcmd->forwardmove, -450.f, 450.f);
	m_pcmd->sidemove = clamp(m_pcmd->sidemove, -450.f, 450.f);
	m_pcmd->upmove = clamp(m_pcmd->upmove, -320.f, 320.f);
}

inline void Math::SinCos(float a, float* s, float* c)
{
	*s = sin(a);
	*c = cos(a);
}

inline void Math::VectorAngle(const Vector& angles, Vector& forward, Vector& right, Vector& up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles[1]), &sy, &cy);
	SinCos(DEG2RAD(angles[0]), &sp, &cp);
	SinCos(DEG2RAD(angles[2]), &sr, &cr);

	forward.x = (cp * cy);
	forward.y = (cp * sy);
	forward.z = (-sp);
	right.x = (-1 * sr * sp * cy + -1 * cr * -sy);
	right.y = (-1 * sr * sp * sy + -1 * cr * cy);
	right.z = (-1 * sr * cp);
	up.x = (cr * sp * cy + -sr * -sy);
	up.y = (cr * sp * sy + -sr * cy);
	up.z = (cr * cp);
}

inline float Math::WorldDistance(const Vector& vecStart, const Vector& vecEnd)
{
	float fX = powf(vecEnd.x - vecStart.x, 2.f);
	float fY = powf(vecEnd.y - vecStart.y, 2.f);
	float fZ = powf(vecEnd.z - vecStart.z, 2.f);

	return sqrtf(fX + fY + fZ);
}

inline void Math::AngleVectors(const Vector& angles, Vector* forward, Vector* right, Vector* up)
{
	float sr, sp, sy, cr, cp, cy;

	SinCos(DEG2RAD(angles.x), &sp, &cp);
	SinCos(DEG2RAD(angles.y), &sy, &cy);
	SinCos(DEG2RAD(angles.z), &sr, &cr);

	if (forward)
	{
		forward->x = cp * cy;
		forward->y = cp * sy;
		forward->z = -sp;
	}

	if (right)
	{
		right->x = (-1 * sr * sp * cy + -1 * cr * -sy);
		right->y = (-1 * sr * sp * sy + -1 * cr * cy);
		right->z = -1 * sr * cp;
	}

	if (up)
	{
		up->x = (cr * sp * cy + -sr * -sy);
		up->y = (cr * sp * sy + -sr * cy);
		up->z = cr * cp;
	}
}

inline void Math::AngleVectors(const Vector& angles, Vector& forward)
{

	float	sp, sy, cp, cy;

	sy = sin(DEG2RAD(angles[1]));
	cy = cos(DEG2RAD(angles[1]));

	sp = sin(DEG2RAD(angles[0]));
	cp = cos(DEG2RAD(angles[0]));

	forward.x = cp * cy;
	forward.y = cp * sy;
	forward.z = -sp;
}

inline void Math::VectorAngles(const Vector& forward, Vector& angles)
{
	if (forward[1] == 0.0f && forward[0] == 0.0f)
	{
		angles[0] = (forward[2] > 0.0f) ? 270.0f : 90.0f; // Pitch (up/down)
		angles[1] = 0.0f;  //yaw left/right
	}
	else
	{
		angles[0] = atan2(-forward[2], forward.Length2D()) * -180 / M_PI_F;
		angles[1] = atan2(forward[1], forward[0]) * 180 / M_PI_F;

		if (angles[1] > 90)
			angles[1] -= 180;
		else if (angles[1] < 90)
			angles[1] += 180;
		else if (angles[1] == 90)
			angles[1] = 0;
	}

	angles[2] = 0.0f;
}

inline float Math::AngleDistance(const Vector& vecStart, const Vector& vecEnd, const float& fDistance)
{
	Vector vecDifference = vecEnd - vecStart;

	float fPitch = ((DEG2RAD(fabsf(vecDifference.x)) * fDistance) * 0.1905f);
	float fYaw = ((DEG2RAD(fabsf(vecDifference.y)) * fDistance) * 0.1905f);

	return sqrtf(powf(fPitch, 2.f) + powf(fYaw, 2.f));
}

inline float Math::NormalizeAngle(const float& fAxis)
{
	return std::isfinite(fAxis) ? std::remainder(fAxis, 360.0f) : 0.f;
}

inline float Math::NormalizeVector(Vector& vec)
{
	const float fLength = vec.Length();
	vec = fLength ? vec / fLength : Vector();

	return fLength;
}

inline Vector Math::VectorAngles(const Vector& vecDirection)
{
	float fPitch, fYaw = 0.f;

	if (vecDirection.x && vecDirection.y)
	{
		fPitch = RAD2DEG(std::atan2f(-vecDirection.z, vecDirection.Length2D()));
		fPitch += fPitch < 0.f ? 360.f : 0.f;

		fYaw = RAD2DEG(std::atan2f(vecDirection.y, vecDirection.x));
		fYaw += fYaw < 0.f ? 360.f : 0.f;
	}
	else
	{
		fPitch = vecDirection.z > 0.f ? 270.f : 90.f;
	}

	return Vector(fPitch, fYaw, 0.f);
}

inline Vector Math::GetBoneAngles(const Vector& BonePos, const Vector& LocalEyeAngles)
{
	Vector vecForward = BonePos - LocalEyeAngles;
	Math::NormalizeVector(vecForward);

	Vector vecAngles = Math::VectorAngles(vecForward);
	return vecAngles;
}

inline float Math::DotProduct(const Vector& a, const Vector& b)
{
	return (a.x * b.x + a.y * b.y + a.z * b.z);
}

inline float Math::ToRadians(float degrees)
{
	return (degrees * (M_PI / 180.0f));
}

inline float Math::ToDegrees(float radians)
{
	return (radians * (180.0f / M_PI));
}

inline void Math::VectorTransform(const Vector in1, const matrix3x4_t& in2, Vector& out)
{
	out[0] = Math::DotProduct(in1, Vector(in2[0][0], in2[0][1], in2[0][2])) + in2[0][3];
	out[1] = Math::DotProduct(in1, Vector(in2[1][0], in2[1][1], in2[1][2])) + in2[1][3];
	out[2] = Math::DotProduct(in1, Vector(in2[2][0], in2[2][1], in2[2][2])) + in2[2][3];
}