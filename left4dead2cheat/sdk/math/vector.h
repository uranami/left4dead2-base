#pragma once
#include <cmath>

typedef float vec_t;

#define FLOAT32_NAN_BITS	(unsigned long)0x7FC00000
#define FLOAT32_NAN			BitsToFloat(FLOAT32_NAN_BITS)
#define VEC_T_NAN			FLOAT32_NAN
#define INVALID_VECTOR Vector(VEC_T_NAN, VEC_T_NAN, VEC_T_NAN)
#define INVALID_QANGLE QAngle(VEC_T_NAN, VEC_T_NAN, VEC_T_NAN)
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
class QAngle;

class matrix3x4
{
public:
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

	float m[3][4];
};

class matrix4x4
{
public:
	inline float* operator[](int i)
	{
		return m[i];
	}

	inline const float* operator[](int i) const
	{
		return m[i];
	}

	float m[4][4];
};

class Vector
{
public:
	Vector(vec_t x = 0.0f, vec_t y = 0.0f, vec_t z = 0.0f);
	Vector(const QAngle& angles);
	Vector(const vec_t* v);

	void Invalidate();
	bool IsValid() const;
	bool IsZero(float tolerance = 1e-6f) const;
	void Init(vec_t x = 0.0f, vec_t y = 0.0f, vec_t z = 0.0f);
	void SetZero();


	vec_t Dot(const Vector& v) const;

	Vector Cross(const Vector& v) const;

	Vector Normalize() const;

	vec_t Length() const;
	vec_t Length2D() const;

	vec_t LengthSqr() const;

	vec_t Length2DSqr() const;


	Vector Scale(vec_t f) const;

	QAngle toAngles() const;

	vec_t DistTo(const Vector& vOther) const;
	vec_t DistToSqr(const Vector& vOther) const;

#ifdef ALLOW_CAST_POINTER

	operator vec_t* ();
#endif

public:
	float operator[](int index) const;
	float& operator[](int index);

	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;

	Vector operator+(const Vector& v) const;
	Vector operator-(const Vector& v) const;
	Vector operator*(const Vector& v) const;
	Vector operator/(const Vector& v) const;
	Vector operator+(const vec_t& f) const;
	Vector operator-(const vec_t& f) const;
	Vector operator*(const vec_t& f) const;
	Vector operator/(const vec_t& f) const;
	Vector operator-() const;

	Vector& operator+=(const Vector& v);
	Vector& operator-=(const Vector& v);
	Vector& operator*=(const Vector& v);
	Vector& operator/=(const Vector& v);
	Vector& operator+=(const vec_t& f);
	Vector& operator-=(const vec_t& f);
	Vector& operator*=(const vec_t& f);
	Vector& operator/=(const vec_t& f);

#ifdef PRIVATE_VECTOR_TYPE
private:
#else
public:
#endif
	vec_t x, y, z;
};


class QAngle
{
public:
	QAngle(vec_t x = 0.0f, vec_t y = 0.0f, vec_t z = 0.0f);
	QAngle(const Vector& vector);

	void Invalidate();
	bool IsValid() const;
	bool IsZero(float tolerance = 1e-6f) const;
	void Init(vec_t x = 0.0f, vec_t y = 0.0f, vec_t z = 0.0f);

	Vector Forward() const;
	Vector Right() const;
	Vector Up() const;
	void Zero();
	QAngle Normalize() const;
	QAngle Clamp() const;

public:
	float operator[](int index) const;
	float& operator[](int index);

	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	QAngle operator+(const QAngle& v) const;
	QAngle operator-(const QAngle& v) const;
	QAngle operator*(const QAngle& v) const;
	QAngle operator/(const QAngle& v) const;
	QAngle operator+(const vec_t& f) const;
	QAngle operator-(const vec_t& f) const;
	QAngle operator*(const vec_t& f) const;
	QAngle operator/(const vec_t& f) const;
	QAngle operator-() const;

	QAngle& operator+=(const QAngle& v);
	QAngle& operator-=(const QAngle& v);
	QAngle& operator*=(const QAngle& v);
	QAngle& operator/=(const QAngle& v);
	QAngle& operator+=(const vec_t& f);
	QAngle& operator-=(const vec_t& f);
	QAngle& operator*=(const vec_t& f);
	QAngle& operator/=(const vec_t& f);

#ifdef PRIVATE_VECTOR_TYPE
private:
#else
public:
#endif
	vec_t x, y, z;
};

// 2D Vector
class Vector2D
{
public:
	// Members
	vec_t x, y;

	// Construction/destruction:
	Vector2D(void);
	Vector2D(vec_t X, vec_t Y);
	Vector2D(vec_t* clr);

	Vector2D(const Vector2D& vOther)
	{
		x = vOther.x; y = vOther.y;
	}

	// Initialization
	void Init(vec_t ix = 0.0f, vec_t iy = 0.0f);
	// TODO (Ilya): Should there be an init that takes a single float for consistency?

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	vec_t operator[](int i) const;
	vec_t& operator[](int i);

	// Base address...
	vec_t* Base();
	vec_t const* Base() const;

	// Initialization methods
	void Random(vec_t minVal, vec_t maxVal);
	void Zero(); ///< zero out a vector

				 // equality
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	// arithmetic operations
	Vector2D& operator+=(const Vector2D& v)
	{
		x += v.x; y += v.y;
		return *this;
	}

	Vector2D& operator-=(const Vector2D& v)
	{
		x -= v.x; y -= v.y;
		return *this;
	}

	Vector2D& operator*=(float fl)
	{
		x *= fl;
		y *= fl;
		return *this;
	}

	Vector2D& operator*=(const Vector2D& v)
	{
		x *= v.x;
		y *= v.y;
		return *this;
	}

	Vector2D& operator/=(const Vector2D& v)
	{
		x /= v.x;
		y /= v.y;
		return *this;
	}

	// this ought to be an opcode.
	Vector2D& operator+=(float fl)
	{
		x += fl;
		y += fl;
		return *this;
	}

	// this ought to be an opcode.
	Vector2D& operator/=(float fl)
	{
		x /= fl;
		y /= fl;
		return *this;
	}
	Vector2D& operator-=(float fl)
	{
		x -= fl;
		y -= fl;
		return *this;
	}

	// negate the vector components
	void Negate();

	// Get the vector's magnitude.
	vec_t Length() const;

	// Get the vector's magnitude squared.
	vec_t LengthSqr(void) const
	{
		return (x * x + y * y);
	}

	// return true if this vector is (0,0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance&&
			y > -tolerance && y < tolerance);
	}

	vec_t NormalizeInPlace();
	Vector2D Normalized() const;
	bool IsLengthGreaterThan(float val) const;
	bool IsLengthLessThan(float val) const;

	// check if a vector is within the box defined by two other vectors
	bool WithinAABox(Vector2D const& boxmin, Vector2D const& boxmax);

	// Get the distance from this vector to the other one.
	vec_t DistTo(const Vector2D& vOther) const;

	// Get the distance from this vector to the other one squared.
	// NJS: note, VC wasn't inlining it correctly in several deeply nested inlines due to being an 'out of line' .  
	// may be able to tidy this up after switching to VC7
	vec_t DistToSqr(const Vector2D& vOther) const
	{
		Vector2D delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;

		return delta.LengthSqr();
	}

	// Copy
	void CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual vector equation (because it's done per-component
	// rather than per-vector).
	void MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

	// Dot product.
	vec_t Dot(const Vector2D& vOther) const;

	// assignment
	Vector2D& operator=(const Vector2D& vOther);

	// 2d
	vec_t Length2D(void) const;
	vec_t Length2DSqr(void) const;

	/// Get the component of this vector parallel to some other given vector
	Vector2D  ProjectOnto(const Vector2D& onto);

	// copy constructors
	// Vector2D(const Vector2D &vOther);

	// arithmetic operations
	Vector2D operator-(void) const;

	Vector2D operator+(const Vector2D& v) const;
	Vector2D operator-(const Vector2D& v) const;
	Vector2D operator*(const Vector2D& v) const;
	Vector2D operator/(const Vector2D& v) const;
	Vector2D operator*(float fl) const;
	Vector2D operator/(float fl) const;

	// Cross product between two vectors.
	Vector2D Cross(const Vector2D& vOther) const;

	// Returns a vector with the min or max in X, Y, and Z.
	Vector2D Min(const Vector2D& vOther) const;
	Vector2D Max(const Vector2D& vOther) const;
};

typedef Vector2D vec2_t;

class Vector4D
{
public:
	Vector4D(vec_t x = 0.0f, vec_t y = 0.0f, vec_t z = 0.0f, vec_t w = 0.0f);

#ifdef PRIVATE_VECTOR_TYPE
private:
#else
public:
#endif
	vec_t x, y, z, w;
};

inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline unsigned long const& FloatBits(float const& f)
{
	return *reinterpret_cast<unsigned long const*>(&f);
}

inline float BitsToFloat(unsigned long i)
{
	return *reinterpret_cast<float*>(&i);
}

inline float IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

inline unsigned long FloatAbsBits(float f)
{
	return FloatBits(f) & 0x7FFFFFFF;
}

inline float FloatMakeNegative(float f)
{
	return BitsToFloat(FloatBits(f) | 0x80000000);
}

inline float FloatMakePositive(float f)
{
	return abs(f);
}

inline float FloatNegate(float f)
{
	return BitsToFloat(FloatBits(f) ^ 0x80000000);
}
