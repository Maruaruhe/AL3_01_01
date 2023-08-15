#include "Vec3.h"
#include <cmath>
#include <assert.h>

Vector3 Add(Vector3 v1, Vector3 v2) {
	Vector3 result;
	result.x = v1.x + v2.x;
	result.y = v1.y + v2.y;
	result.z = v1.z + v2.z;
	return result;
}

Vector3 Subtract(Vector3 v1, Vector3 v2) {
	Vector3 result;
	result.x = v1.x - v2.x;
	result.y = v1.y - v2.y;
	result.z = v1.z - v2.z;
	return result;
}

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix) {
	Vector3 result;
	result.x = vector.x * matrix.m[0][0] + vector.y * matrix.m[1][0] + vector.z * matrix.m[2][0] +
	           1.0f * matrix.m[3][0];
	result.y = vector.x * matrix.m[0][1] + vector.y * matrix.m[1][1] + vector.z * matrix.m[2][1] +
	           1.0f * matrix.m[3][1];
	result.z = vector.x * matrix.m[0][2] + vector.y * matrix.m[1][2] + vector.z * matrix.m[2][2] +
	           1.0f * matrix.m[3][2];
	float w = vector.x * matrix.m[0][3] + vector.y * matrix.m[1][3] + vector.z * matrix.m[2][3] +
	          1.0f * matrix.m[3][3];
	assert(w != 0.0f);
	result.x /= w;
	result.y /= w;
	result.z /= w;
	return result;
}

Vector3 TransformNormal(const Vector3& velocity, const Matrix4x4& matrix) {
	Vector3 result{
	    velocity.x * matrix.m[0][0] + velocity.y * matrix.m[1][0] + velocity.z * matrix.m[2][0],
	    velocity.x * matrix.m[0][1] + velocity.y * matrix.m[1][1] + velocity.z * matrix.m[2][1],
	    velocity.x * matrix.m[0][2] + velocity.y * matrix.m[1][2] + velocity.z * matrix.m[2][2]};
	return result;
}

Vector3 Cross(const Vector3& vector1, const Vector3& vector2) {
	Vector3 result;
	result.x = vector1.y * vector2.z - vector1.z * vector2.y;
	result.y = vector1.z * vector2.x - vector1.x * vector2.z;
	result.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return result;
}

Vector3 Normalize(const Vector3& v) {
	Vector3 num = {v.x / Length(v), v.y / Length(v), v.z / Length(v)};
	return num;
}

float Length(const Vector3& v) {
	float num = {sqrtf(v.x * v.x + v.y * v.y + v.z * v.z)};
	return num;
}

float dotXY(Vector3 v1, Vector3 v2) { 
	float result;
	Vector3 distance = {};
	distance.x = v1.x - v2.x;
	distance.y = v1.y - v2.y;
	result = sqrt(pow(distance.x, 2) + pow(distance.y, 2));
	return result;
}
float dotXZ(Vector3 v1, Vector3 v2) { 
	float result;
	Vector3 distance = {};
	distance.x = v1.x - v2.x;
	distance.z = v1.z - v2.z;
	result = sqrt(pow(distance.x, 2) + pow(distance.z, 2));
	return result;
}
float dotYZ(Vector3 v1, Vector3 v2) { 
	float result;
	Vector3 distance = {};
	distance.y = v1.y - v2.y;
	distance.z = v1.z - v2.z;
	result = sqrt(pow(distance.y, 2) + pow(distance.z, 2));
	return result;
}

float Dot(const Vector3& v1, const Vector3& v2) {
	float dot = 0.0f;

	dot = v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;

	return dot;
}

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 v3 = {};

	v3.x = v1.x + t * (v2.x - v1.x);
	v3.y = v1.y + t * (v2.y - v1.y);
	v3.z = v1.z + t * (v2.z - v1.z);

	return v3;
}

Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t) {
	Vector3 v3 = {};

	if (v1.x == v2.x && v1.y == v2.y && v1.z == v2.z) {
		v3 = Lerp(v1, v2, t);
		return v3;
	} else {
		// 2ÉxÉNÉgÉãä‘ÇÃäpìxÅiâsäpë§Åj
		float angle = std::acos(Dot(v1, v2));

		// sinÉ∆
		float SinTh = std::sin(angle);

		// ï‚ä‘åWêî
		float Ps = std::sin(angle * (1 - t));
		float Pe = std::sin(angle * t);

		v3.x = (Ps * v1.x + Pe * v2.x) / SinTh;
		v3.y = (Ps * v1.y + Pe * v2.y) / SinTh;
		v3.z = (Ps * v1.z + Pe * v2.z) / SinTh;

		// àÍâûê≥ãKâªÇµÇƒãÖñ ê¸å`ï‚ä‘Ç…
		Normalize(v3);

		return v3;
	}
}

Vector3 Multiply(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {v1.x * v2.x, v1.y * v2.y, v1.z * v2.z};
	return result;
}

Vector3 Division(const Vector3& v1, const Vector3& v2) {
	Vector3 result = {v1.x / v2.x, v1.y / v2.y, v1.z / v2.z};
	return result;
}