#include "vector.h"
#include <cmath>
#include <utility>

#ifndef M_PI
#define M_PI	3.14159265358979323846
#define M_PI_F	((float)M_PI)
#endif

#ifndef RAD2DEG
#define RAD2DEG(x)  ((float)(x) * (float)(180.f / M_PI_F))
#define RadiansToDegrees RAD2DEG
#define DEG2RAD(x)  ((float)(x) * (float)(M_PI_F / 180.f))
#define DegreesToRadians DEG2RAD
#endif

#ifndef Assert
#define Assert(_v)			
#endif

#define CHECK_VALID(_v)		Assert((_v).IsValid())

#ifndef FLOAT32_NAN_BITS
#define FLOAT32_NAN_BITS	(unsigned long)0x7FC00000
#define FLOAT32_NAN			BitsToFloat(FLOAT32_NAN_BITS)
#define VEC_T_NAN			FLOAT32_NAN
#endif

void inline SinCos(float radians, float* sine, float* cosine)
{
	*sine = sin(radians);
	*cosine = cos(radians);
}

Vector::Vector(vec_t x, vec_t y, vec_t z) : x(x), y(y), z(z)
{
}

Vector::Vector(const QAngle& angles)
{
	x = angles.x;
	y = angles.y;
	z = angles.z;
}

Vector::Vector(const vec_t* v) : x(v[0]), y(v[1]), z(v[2])
{
}

void Vector::Invalidate()
{
	x = y = z = VEC_T_NAN;
}

bool Vector::IsValid() const
{
	return (IsFinite(x) && IsFinite(y) && IsFinite(z));
}

bool Vector::IsZero(float tolerance) const
{
	return (x > -tolerance && x < tolerance&& y > -tolerance && y < tolerance&& z > -tolerance && z < tolerance);
}

void Vector::Init(vec_t x, vec_t y, vec_t z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

void Vector::SetZero()
{
	x = y = z = 0.0f;
}

vec_t Vector::Dot(const Vector& v) const
{
	return (x * v.x + y * v.y + z * v.z);
}

Vector Vector::Cross(const Vector& v) const
{
	return Vector(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x);
}

Vector Vector::Normalize() const
{
	vec_t length = sqrt(x * x + y * y + z * z);
	return Vector(x / length, y / length, z / length);
}

vec_t Vector::Length() const
{
	return sqrt(x * x + y * y + z * z);
}

vec_t Vector::Length2D() const
{
	return sqrt(x * x + y * y);
}

vec_t Vector::LengthSqr() const
{
	return (x * x + y * y + z * z);
}

vec_t Vector::Length2DSqr() const
{
	return (x * x + y * y);
}

inline void AngleMatrix(const QAngle& angles, matrix3x4& matrix)
{
	float sp, sy, sr, cp, cy, cr;

	SinCos(DEG2RAD(angles.x), &sp, &cp);
	SinCos(DEG2RAD(angles.y), &sy, &cy);
	SinCos(DEG2RAD(angles.z), &sr, &cr);

	matrix[0][0] = cp * cy;
	matrix[1][0] = cp * sy;
	matrix[2][0] = -sp;

	float crcy = cr * cy;
	float crsy = cr * sy;
	float srcy = sr * cy;
	float srsy = sr * sy;

	matrix[0][1] = sp * srcy - crsy;
	matrix[1][1] = sp * srsy + crcy;
	matrix[2][1] = sr * cp;

	matrix[0][2] = sp * crcy + srsy;
	matrix[1][2] = sp * crsy - srcy;
	matrix[2][2] = cr * cp;

	matrix[0][3] = 0.0f;
	matrix[1][3] = 0.0f;
	matrix[2][3] = 0.0f;
}

Vector Vector::Scale(vec_t f) const
{
	return Vector(x * f, y * f, z * f);
}

QAngle Vector::toAngles() const
{
	vec_t tmp, yaw, pitch;
	if (x == 0.0f && y == 0.0f)
	{
		yaw = 0.0f;
		if (z > 0.0f)
			pitch = 270.0f;
		else
			pitch = 90.0f;
	}
	else
	{
		yaw = static_cast<float>(atan2(y, x) * 180.0f / M_PI);
		if (yaw < 0.0f)
			yaw += 360.0f;

		tmp = sqrt(x * x + y * y);
		pitch = static_cast<float>(atan2(-z, tmp) * 180.0f / M_PI);
		if (pitch < 0.0f)
			pitch += 360.0f;
	}

	return QAngle(pitch, yaw, 0.0f);
}

vec_t Vector::DistTo(const Vector& vOther) const
{
	return (*this - vOther).Length();
}

vec_t Vector::DistToSqr(const Vector& vOther) const
{
	return (*this - vOther).LengthSqr();
}

#ifdef ALLOW_CAST_POINTER
Vector::operator vec_t* ()
{
	return &x;
}
#endif

float Vector::operator[](int index) const
{
	if (index <= 0)
		return x;
	if (index == 1)
		return y;
	return z;
}

float& Vector::operator[](int index)
{
	if (index <= 0)
		return x;
	if (index == 1)
		return y;
	return z;
}

bool Vector::operator==(const Vector& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

bool Vector::operator!=(const Vector& v) const
{
	return (x != v.x || y != v.y || z != v.z);
}

Vector Vector::operator+(const Vector& v) const
{
	return Vector(x + v.x, y + v.y, z + v.z);
}

Vector Vector::operator-(const Vector& v) const
{
	return Vector(x - v.x, y - v.y, z - v.z);
}

Vector Vector::operator*(const Vector& v) const
{
	return Vector(x * v.x, y * v.y, z * v.z);
}

Vector Vector::operator/(const Vector& v) const
{
	return Vector(x / v.x, y / v.y, z / v.z);
}

Vector Vector::operator+(const vec_t& f) const
{
	return Vector(x + f, y + f, z + f);
}

Vector Vector::operator-(const vec_t& f) const
{
	return Vector(x - f, y - f, z - f);
}

Vector Vector::operator*(const vec_t& f) const
{
	return Vector(x * f, y * f, z * f);
}

Vector Vector::operator/(const vec_t& f) const
{
	return Vector(x / f, y / f, z / f);
}

Vector Vector::operator-() const
{
	return Vector(-x, -y, -z);
}

Vector& Vector::operator+=(const Vector& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

Vector& Vector::operator-=(const Vector& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

Vector& Vector::operator*=(const Vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

Vector& Vector::operator/=(const Vector& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

Vector& Vector::operator+=(const vec_t& f)
{
	x += f;
	y += f;
	z += f;
	return *this;
}

Vector& Vector::operator-=(const vec_t& f)
{
	x -= f;
	y -= f;
	z -= f;
	return *this;
}

Vector& Vector::operator*=(const vec_t& f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}

Vector& Vector::operator/=(const vec_t& f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

QAngle::QAngle(vec_t x, vec_t y, vec_t z) : x(x), y(y), z(z)
{
}

QAngle::QAngle(const Vector& vector)
{
	x = vector.x;
	y = vector.y;
	z = vector.z;
}

void QAngle::Invalidate()
{
	x = y = z = VEC_T_NAN;
}

bool QAngle::IsValid() const
{
	return (IsFinite(x) && IsFinite(y) && IsFinite(z));
}

bool QAngle::IsZero(float tolerance) const
{
	return (x > -tolerance && x < tolerance&& y > -tolerance && y < tolerance&& z > -tolerance && z < tolerance);
}

void QAngle::Init(vec_t x, vec_t y, vec_t z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Vector QAngle::Forward() const
{
	vec_t sp, sy, cp, cy;
	SinCos(DEG2RAD(y), &sy, &cy);
	SinCos(DEG2RAD(x), &sp, &cp);
	return Vector(cp * cy, cp * sy, -sp);
}

Vector QAngle::Right() const
{
	vec_t sr, sp, sy, cr, cp, cy;
	SinCos(DEG2RAD(y), &sy, &cy);
	SinCos(DEG2RAD(x), &sp, &cp);
	SinCos(DEG2RAD(z), &sr, &cr);
	return Vector(-1 * sr * sp * cy + -1 * cr * -sy,
		-1 * sr * sp * sy + -1 * cr * cy,
		-1 * sr * cp);
}

Vector QAngle::Up() const
{
	vec_t sr, sp, sy, cr, cp, cy;
	SinCos(DEG2RAD(y), &sy, &cy);
	SinCos(DEG2RAD(x), &sp, &cp);
	SinCos(DEG2RAD(z), &sr, &cr);
	return Vector(cr * sp * cy + -sr * -sy,
		cr * sp * sy + -sr * cy,
		cr * cp);
}

QAngle QAngle::Normalize() const
{
	QAngle angles(x, y, z);
	for (int i = 0; i < 3; ++i)
	{
		if (angles[i] < -180.0f)
			angles[i] += 360.0f;

		if (angles[i] > 180.0f)
			angles[i] -= 360.0f;
	}

	return std::move(angles);
}

void QAngle::Zero()
{
	x = y = z = 0.f;
}

QAngle QAngle::Clamp() const
{
	QAngle angles(x, y, z);

	if (angles.x > 89.0f && angles.x <= 180.0f)
		angles.x = 89.0f;

	if (angles.x > 180.0f)
		angles.x = angles.x - 360.0f;

	if (angles.x < -89.0f)
		angles.x = -89.0f;

	angles.y = fmod(angles.y + 180.0f, 360.0f) - 180.0f;
	angles.z = 0;

	return std::move(angles);
}

float QAngle::operator[](int index) const
{
	if (index <= 0)
		return x;
	if (index == 1)
		return y;
	return z;
}

float& QAngle::operator[](int index)
{
	if (index <= 0)
		return x;
	if (index == 1)
		return y;
	return z;
}

bool QAngle::operator==(const QAngle& v) const
{
	return (x == v.x && y == v.y && z == v.z);
}

bool QAngle::operator!=(const QAngle& v) const
{
	return (x != v.x || y != v.y || z != v.z);
}

QAngle QAngle::operator+(const QAngle& v) const
{
	return QAngle(x + v.x, y + v.y, z + v.z);
}

QAngle QAngle::operator-(const QAngle& v) const
{
	return QAngle(x - v.x, y - v.y, z - v.z);
}

QAngle QAngle::operator*(const QAngle& v) const
{
	return QAngle(x * v.x, y * v.y, z * v.z);
}

QAngle QAngle::operator/(const QAngle& v) const
{
	return QAngle(x / v.x, y / v.y, z / v.z);
}

QAngle QAngle::operator+(const vec_t& f) const
{
	return QAngle(x + f, y + f, z + f);
}

QAngle QAngle::operator-(const vec_t& f) const
{
	return QAngle(x - f, y - f, z - f);
}

QAngle QAngle::operator*(const vec_t& f) const
{
	return QAngle(x * f, y * f, z * f);
}

QAngle QAngle::operator/(const vec_t& f) const
{
	return QAngle(x / f, y / f, z / f);
}

QAngle QAngle::operator-() const
{
	return QAngle(-x, -y, -z);
}

QAngle& QAngle::operator+=(const QAngle& v)
{
	x += v.x;
	y += v.y;
	z += v.z;
	return *this;
}

QAngle& QAngle::operator-=(const QAngle& v)
{
	x -= v.x;
	y -= v.y;
	z -= v.z;
	return *this;
}

QAngle& QAngle::operator*=(const QAngle& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;
	return *this;
}

QAngle& QAngle::operator/=(const QAngle& v)
{
	x /= v.x;
	y /= v.y;
	z /= v.z;
	return *this;
}

QAngle& QAngle::operator+=(const vec_t& f)
{
	x += f;
	y += f;
	z += f;
	return *this;
}

QAngle& QAngle::operator-=(const vec_t& f)
{
	x -= f;
	y -= f;
	z -= f;
	return *this;
}

QAngle& QAngle::operator*=(const vec_t& f)
{
	x *= f;
	y *= f;
	z *= f;
	return *this;
}



QAngle& QAngle::operator/=(const vec_t& f)
{
	x /= f;
	y /= f;
	z /= f;
	return *this;
}

Vector2D::Vector2D(void)
{
}

Vector2D::Vector2D(vec_t X, vec_t Y)
{
	x = X; y = Y;
}

Vector2D::Vector2D(vec_t* clr)
{
	x = clr[0]; y = clr[1];
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

void Vector2D::Init(vec_t ix, vec_t iy)
{
	x = ix; y = iy;
}

void Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
}

void Vector2DClear(Vector2D& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

Vector2D& Vector2D::operator=(const Vector2D& vOther)
{
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

vec_t& Vector2D::operator[](int i)
{
	return ((vec_t*)this)[i];
}

vec_t Vector2D::operator[](int i) const
{
	return ((vec_t*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

vec_t* Vector2D::Base()
{
	return (vec_t*)this;
}

vec_t const* Vector2D::Base() const
{
	return (vec_t const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

bool Vector2D::IsValid() const
{
	return !isinf(x) && !isinf(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

bool Vector2D::operator==(const Vector2D& src) const
{
	return (src.x == x) && (src.y == y);
}

bool Vector2D::operator!=(const Vector2D& src) const
{
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
	dst.x = src.x;
	dst.y = src.y;
}

void Vector2D::CopyToArray(float* rgfl) const
{
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard Math operations
//-----------------------------------------------------------------------------

void Vector2D::Negate()
{
	x = -x; y = -y;
}

void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

void Vector2DMultiply(const Vector2D& a, vec_t b, Vector2D& c)
{
	c.x = a.x * b;
	c.y = a.y * b;
}

void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


void Vector2DDivide(const Vector2D& a, vec_t b, Vector2D& c)
{
	vec_t oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
void Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, vec_t t, Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
vec_t DotProduct2D(const Vector2D& a, const Vector2D& b)
{
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
vec_t Vector2D::Dot(const Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}

vec_t Vector2DNormalize(Vector2D& v)
{
	vec_t l = v.Length();
	if (l != 0.0f) {
		v /= l;
	}
	else {
		v.x = v.y = 0.0f;
	}
	return l;
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
vec_t Vector2DLength(const Vector2D& v)
{
	return (vec_t)sqrt(v.x * v.x + v.y * v.y);
}

vec_t Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

bool Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val * val;
}

bool Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}

vec_t Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}


void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}

//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D* pResult)
{
	Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist) {
		*pResult = vecTarget;
	}
	else {
		vecDelta /= sqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}

//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

Vector2D Vector2D::Min(const Vector2D& vOther) const
{
	return Vector2D(x < vOther.x ? x : vOther.x, y < vOther.y ? y : vOther.y);
}

Vector2D Vector2D::Max(const Vector2D& vOther) const
{
	return Vector2D(x > vOther.x ? x : vOther.x, y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

Vector2D Vector2D::operator-(void) const
{
	return Vector2D(-x, -y);
}

Vector2D Vector2D::operator+(const Vector2D& v) const
{
	Vector2D res;
	Vector2DAdd(*this, v, res);
	return res;
}

Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);
	return res;
}

Vector2D Vector2D::operator*(float fl) const
{
	Vector2D res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

Vector2D Vector2D::operator*(const Vector2D& v) const
{
	Vector2D res;
	Vector2DMultiply(*this, v, res);
	return res;
}

Vector2D Vector2D::operator/(float fl) const
{
	Vector2D res;
	Vector2DDivide(*this, fl, res);
	return res;
}

Vector2D Vector2D::operator/(const Vector2D& v) const
{
	Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

Vector2D operator*(float fl, const Vector2D& v)
{
	return v * fl;
}

Vector4D::Vector4D(vec_t x, vec_t y, vec_t z, vec_t w) : x(x), y(y), z(z), w(w)
{
}