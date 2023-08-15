#include <Vector3.h>
#include <Matrix4x4.h>
#include <math.h>

struct Matrix;

Vector3 Add(Vector3 v1, Vector3 v2);
Vector3 Subtract(Vector3 v1, Vector3 v2);

Vector3 Transform(const Vector3& vector, const Matrix4x4& matrix);
Vector3 TransformNormal(const Vector3& velocity, const Matrix4x4& matrix);

Vector3 Cross(const Vector3& vector1, const Vector3& vector2);

Vector3 Normalize(const Vector3& v);

float Length(const Vector3& v);

Vector3 Normalize(const Vector3& v);

float Length(const Vector3& v);

float dotXY(Vector3 v1, Vector3 v2);
float dotXZ(Vector3 v1, Vector3 v2);
float dotYZ(Vector3 v1, Vector3 v2);

float Dot(const Vector3& v1, const Vector3& v2);

Vector3 Lerp(const Vector3& v1, const Vector3& v2, float t);
Vector3 Slerp(const Vector3& v1, const Vector3& v2, float t);

Vector3 Multiply(const Vector3& v1, const Vector3& v2);

Vector3 Division(const Vector3& v1, const Vector3& v2);