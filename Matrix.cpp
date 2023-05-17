#include "Matrix.h"

Vector3 Add(const Vector3& position, const Vector3& velocity) { 
	Vector3 result;
	result.x = position.x + velocity.x;
	result.y = position.y + velocity.y;
	result.z = position.z + velocity.z;
	return result;
}

Matrix4x4 Add(const Matrix4x4& m1, const Matrix4x4& m2) {
	return {m1.m[0][0] + m2.m[0][0], m1.m[0][1] + m2.m[0][1], m1.m[0][2] + m2.m[0][2],
	        m1.m[0][3] + m2.m[0][3], m1.m[1][0] + m2.m[1][0], m1.m[1][1] + m2.m[1][1],
	        m1.m[1][2] + m2.m[1][2], m1.m[1][3] + m2.m[1][3], m1.m[2][0] + m2.m[2][0],
	        m1.m[2][1] + m2.m[2][1], m1.m[2][2] + m2.m[2][2], m1.m[2][3] + m2.m[2][3],
	        m1.m[3][0] + m2.m[3][0], m1.m[3][1] + m2.m[3][1], m1.m[3][2] + m2.m[3][2],
	        m1.m[3][3] + m2.m[3][3]};
}
Matrix4x4 Subtract(const Matrix4x4& m1, const Matrix4x4& m2) {
	return {m1.m[0][0] - m2.m[0][0], m1.m[0][1] - m2.m[0][1], m1.m[0][2] - m2.m[0][2],
	        m1.m[0][3] - m2.m[0][3], m1.m[1][0] - m2.m[1][0], m1.m[1][1] - m2.m[1][1],
	        m1.m[1][2] - m2.m[1][2], m1.m[1][3] - m2.m[1][3], m1.m[2][0] - m2.m[2][0],
	        m1.m[2][1] - m2.m[2][1], m1.m[2][2] - m2.m[2][2], m1.m[2][3] - m2.m[2][3],
	        m1.m[3][0] - m2.m[3][0], m1.m[3][1] - m2.m[3][1], m1.m[3][2] - m2.m[3][2],
	        m1.m[3][3] - m2.m[3][3]};
}
Matrix4x4 Multiply(const Matrix4x4& m1, const Matrix4x4& m2) {
	Matrix4x4 resultMatrix = {};

	resultMatrix.m[0][0] = m1.m[0][0] * m2.m[0][0] + m1.m[0][1] * m2.m[1][0] +
	                       m1.m[0][2] * m2.m[2][0] + m1.m[0][3] * m2.m[3][0];
	resultMatrix.m[0][1] = m1.m[0][0] * m2.m[0][1] + m1.m[0][1] * m2.m[1][1] +
	                       m1.m[0][2] * m2.m[2][1] + m1.m[0][3] * m2.m[3][1];
	resultMatrix.m[0][2] = m1.m[0][0] * m2.m[0][2] + m1.m[0][1] * m2.m[1][2] +
	                       m1.m[0][2] * m2.m[2][2] + m1.m[0][3] * m2.m[3][2];
	resultMatrix.m[0][3] = m1.m[0][0] * m2.m[0][3] + m1.m[0][1] * m2.m[1][3] +
	                       m1.m[0][2] * m2.m[2][3] + m1.m[0][3] * m2.m[3][3];

	resultMatrix.m[1][0] = m1.m[1][0] * m2.m[0][0] + m1.m[1][1] * m2.m[1][0] +
	                       m1.m[1][2] * m2.m[2][0] + m1.m[1][3] * m2.m[3][0];
	resultMatrix.m[1][1] = m1.m[1][0] * m2.m[0][1] + m1.m[1][1] * m2.m[1][1] +
	                       m1.m[1][2] * m2.m[2][1] + m1.m[1][3] * m2.m[3][1];
	resultMatrix.m[1][2] = m1.m[1][0] * m2.m[0][2] + m1.m[1][1] * m2.m[1][2] +
	                       m1.m[1][2] * m2.m[2][2] + m1.m[1][3] * m2.m[3][2];
	resultMatrix.m[1][3] = m1.m[1][0] * m2.m[0][3] + m1.m[1][1] * m2.m[1][3] +
	                       m1.m[1][2] * m2.m[2][3] + m1.m[1][3] * m2.m[3][3];

	resultMatrix.m[2][0] = m1.m[2][0] * m2.m[0][0] + m1.m[2][1] * m2.m[1][0] +
	                       m1.m[2][2] * m2.m[2][0] + m1.m[2][3] * m2.m[3][0];
	resultMatrix.m[2][1] = m1.m[2][0] * m2.m[0][1] + m1.m[2][1] * m2.m[1][1] +
	                       m1.m[2][2] * m2.m[2][1] + m1.m[2][3] * m2.m[3][1];
	resultMatrix.m[2][2] = m1.m[2][0] * m2.m[0][2] + m1.m[2][1] * m2.m[1][2] +
	                       m1.m[2][2] * m2.m[2][2] + m1.m[2][3] * m2.m[3][2];
	resultMatrix.m[2][3] = m1.m[2][0] * m2.m[0][3] + m1.m[2][1] * m2.m[1][3] +
	                       m1.m[2][2] * m2.m[2][3] + m1.m[2][3] * m2.m[3][3];

	resultMatrix.m[3][0] = m1.m[3][0] * m2.m[0][0] + m1.m[3][1] * m2.m[1][0] +
	                       m1.m[3][2] * m2.m[2][0] + m1.m[3][3] * m2.m[3][0];
	resultMatrix.m[3][1] = m1.m[3][0] * m2.m[0][1] + m1.m[3][1] * m2.m[1][1] +
	                       m1.m[3][2] * m2.m[2][1] + m1.m[3][3] * m2.m[3][1];
	resultMatrix.m[3][2] = m1.m[3][0] * m2.m[0][2] + m1.m[3][1] * m2.m[1][2] +
	                       m1.m[3][2] * m2.m[2][2] + m1.m[3][3] * m2.m[3][2];
	resultMatrix.m[3][3] = m1.m[3][0] * m2.m[0][3] + m1.m[3][1] * m2.m[1][3] +
	                       m1.m[3][2] * m2.m[2][3] + m1.m[3][3] * m2.m[3][3];

	return resultMatrix;
}
Matrix4x4 Inverse(const Matrix4x4& m) {
	Matrix4x4 resultInverse = {};
	float resultNum;
	resultNum = InverseNum(m, 1, 1, 2, 2, 3, 3, 4, 4) + InverseNum(m, 1, 1, 2, 3, 3, 4, 4, 2) +
	            InverseNum(m, 1, 1, 2, 4, 3, 2, 4, 3) - InverseNum(m, 1, 1, 2, 4, 3, 3, 4, 2) -
	            InverseNum(m, 1, 1, 2, 3, 3, 2, 4, 4) - InverseNum(m, 1, 1, 2, 2, 3, 4, 4, 3) -
	            InverseNum(m, 1, 2, 2, 1, 3, 3, 4, 4) - InverseNum(m, 1, 3, 2, 1, 3, 4, 4, 2) -
	            InverseNum(m, 1, 4, 2, 1, 3, 2, 4, 3) + InverseNum(m, 1, 4, 2, 1, 3, 3, 4, 2) +
	            InverseNum(m, 1, 3, 2, 1, 3, 2, 4, 4) + InverseNum(m, 1, 2, 2, 1, 3, 4, 4, 3) +
	            InverseNum(m, 1, 2, 2, 3, 3, 1, 4, 4) + InverseNum(m, 1, 3, 2, 4, 3, 1, 4, 2) +
	            InverseNum(m, 1, 4, 2, 2, 3, 1, 4, 3) - InverseNum(m, 1, 4, 2, 3, 3, 1, 4, 2) -
	            InverseNum(m, 1, 3, 2, 2, 3, 1, 4, 4) - InverseNum(m, 1, 2, 2, 4, 3, 1, 4, 3) -
	            InverseNum(m, 1, 2, 2, 3, 3, 2, 4, 1) - InverseNum(m, 1, 3, 2, 4, 3, 2, 4, 1) -
	            InverseNum(m, 1, 4, 2, 2, 3, 3, 4, 1) + InverseNum(m, 1, 4, 2, 3, 3, 2, 4, 1) +
	            InverseNum(m, 1, 3, 2, 2, 3, 4, 4, 1) + InverseNum(m, 1, 2, 2, 4, 3, 3, 4, 1);

	resultInverse.m[0][0] = (InverseNum2(m, 2, 2, 3, 3, 4, 4) + InverseNum2(m, 2, 3, 3, 4, 4, 2) +
	                         InverseNum2(m, 2, 4, 3, 2, 4, 3) - InverseNum2(m, 2, 4, 3, 3, 4, 2) -
	                         InverseNum2(m, 2, 3, 3, 2, 4, 4) - InverseNum2(m, 2, 2, 3, 4, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[0][1] = (InverseNum2(m, 1, 4, 3, 3, 4, 2) + InverseNum2(m, 1, 3, 3, 2, 4, 4) +
	                         InverseNum2(m, 1, 2, 3, 4, 4, 3) - InverseNum2(m, 1, 2, 3, 3, 4, 4) -
	                         InverseNum2(m, 1, 3, 3, 4, 4, 2) - InverseNum2(m, 1, 4, 3, 2, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[0][2] = (InverseNum2(m, 1, 2, 2, 3, 4, 4) + InverseNum2(m, 1, 3, 2, 4, 4, 2) +
	                         InverseNum2(m, 1, 4, 2, 2, 4, 3) - InverseNum2(m, 1, 4, 2, 3, 4, 2) -
	                         InverseNum2(m, 1, 3, 2, 2, 4, 4) - InverseNum2(m, 1, 2, 2, 4, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[0][3] = (InverseNum2(m, 1, 4, 2, 3, 3, 2) + InverseNum2(m, 1, 3, 2, 2, 3, 4) +
	                         InverseNum2(m, 1, 2, 2, 4, 3, 3) - InverseNum2(m, 1, 2, 2, 3, 3, 4) -
	                         InverseNum2(m, 1, 3, 2, 4, 3, 2) - InverseNum2(m, 1, 4, 2, 2, 3, 3)) *
	                        (1 / resultNum);

	resultInverse.m[1][0] = (InverseNum2(m, 2, 4, 3, 3, 4, 1) + InverseNum2(m, 2, 3, 3, 1, 4, 4) +
	                         InverseNum2(m, 2, 1, 3, 4, 4, 3) - InverseNum2(m, 2, 1, 3, 3, 4, 4) -
	                         InverseNum2(m, 2, 3, 3, 4, 4, 1) - InverseNum2(m, 2, 4, 3, 1, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[1][1] = (InverseNum2(m, 1, 1, 3, 3, 4, 4) + InverseNum2(m, 1, 3, 3, 4, 4, 1) +
	                         InverseNum2(m, 1, 4, 3, 1, 4, 3) - InverseNum2(m, 1, 4, 3, 3, 4, 1) -
	                         InverseNum2(m, 1, 3, 3, 1, 4, 4) - InverseNum2(m, 1, 1, 3, 4, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[1][2] = (InverseNum2(m, 1, 4, 2, 3, 4, 1) + InverseNum2(m, 1, 3, 2, 1, 4, 4) +
	                         InverseNum2(m, 1, 1, 2, 4, 4, 3) - InverseNum2(m, 1, 1, 2, 3, 4, 4) -
	                         InverseNum2(m, 1, 3, 2, 4, 4, 1) - InverseNum2(m, 1, 4, 2, 1, 4, 3)) *
	                        (1 / resultNum);
	resultInverse.m[1][3] = (InverseNum2(m, 1, 1, 2, 3, 3, 4) + InverseNum2(m, 1, 3, 2, 4, 3, 1) +
	                         InverseNum2(m, 1, 4, 2, 1, 3, 3) - InverseNum2(m, 1, 4, 2, 3, 3, 1) -
	                         InverseNum2(m, 1, 3, 2, 1, 3, 4) - InverseNum2(m, 1, 1, 2, 4, 3, 3)) *
	                        (1 / resultNum);

	resultInverse.m[2][0] = (InverseNum2(m, 2, 1, 3, 2, 4, 4) + InverseNum2(m, 2, 2, 3, 4, 4, 1) +
	                         InverseNum2(m, 2, 4, 3, 1, 4, 2) - InverseNum2(m, 2, 4, 3, 2, 4, 1) -
	                         InverseNum2(m, 2, 2, 3, 1, 4, 4) - InverseNum2(m, 2, 1, 3, 4, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[2][1] = (InverseNum2(m, 1, 4, 3, 2, 4, 1) + InverseNum2(m, 1, 2, 3, 1, 4, 4) +
	                         InverseNum2(m, 1, 1, 3, 4, 4, 2) - InverseNum2(m, 1, 1, 3, 2, 4, 4) -
	                         InverseNum2(m, 1, 2, 3, 4, 4, 1) - InverseNum2(m, 1, 4, 3, 1, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[2][2] = (InverseNum2(m, 1, 1, 2, 2, 4, 4) + InverseNum2(m, 1, 2, 2, 4, 4, 1) +
	                         InverseNum2(m, 1, 4, 2, 1, 4, 2) - InverseNum2(m, 1, 4, 2, 2, 4, 1) -
	                         InverseNum2(m, 1, 2, 2, 1, 4, 4) - InverseNum2(m, 1, 1, 2, 4, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[2][3] = (InverseNum2(m, 1, 4, 2, 2, 3, 1) + InverseNum2(m, 1, 2, 2, 1, 3, 4) +
	                         InverseNum2(m, 1, 1, 2, 4, 3, 2) - InverseNum2(m, 1, 1, 2, 2, 3, 4) -
	                         InverseNum2(m, 1, 2, 2, 4, 3, 1) - InverseNum2(m, 1, 4, 2, 1, 3, 2)) *
	                        (1 / resultNum);

	resultInverse.m[3][0] = (InverseNum2(m, 2, 3, 3, 2, 4, 1) + InverseNum2(m, 2, 2, 3, 1, 4, 1) +
	                         InverseNum2(m, 2, 1, 3, 3, 4, 2) - InverseNum2(m, 2, 1, 3, 2, 4, 3) -
	                         InverseNum2(m, 2, 2, 3, 3, 4, 1) - InverseNum2(m, 2, 3, 3, 1, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[3][1] = (InverseNum2(m, 1, 1, 3, 2, 4, 3) + InverseNum2(m, 1, 2, 3, 3, 4, 1) +
	                         InverseNum2(m, 1, 3, 3, 1, 4, 2) - InverseNum2(m, 1, 3, 3, 2, 4, 1) -
	                         InverseNum2(m, 1, 2, 3, 1, 4, 3) - InverseNum2(m, 1, 1, 3, 3, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[3][2] = (InverseNum2(m, 1, 3, 2, 2, 4, 1) + InverseNum2(m, 1, 2, 2, 1, 4, 3) +
	                         InverseNum2(m, 1, 1, 2, 3, 4, 2) - InverseNum2(m, 1, 1, 2, 2, 4, 3) -
	                         InverseNum2(m, 1, 2, 2, 3, 4, 1) - InverseNum2(m, 1, 3, 2, 1, 4, 2)) *
	                        (1 / resultNum);
	resultInverse.m[3][3] = (InverseNum2(m, 1, 1, 2, 2, 3, 3) + InverseNum2(m, 1, 2, 2, 3, 3, 1) +
	                         InverseNum2(m, 1, 3, 2, 1, 3, 2) - InverseNum2(m, 1, 3, 2, 2, 3, 1) -
	                         InverseNum2(m, 1, 2, 2, 1, 3, 3) - InverseNum2(m, 1, 1, 2, 3, 3, 2)) *
	                        (1 / resultNum);

	return resultInverse;
}

float InverseNum(const Matrix4x4& m, int a, int b, int c, int d, int e, int f, int g, int h) {
	float resultNum;
	resultNum = m.m[a - 1][b - 1] * m.m[c - 1][d - 1] * m.m[e - 1][f - 1] * m.m[g - 1][h - 1];
	return resultNum;
}
float InverseNum2(const Matrix4x4& m, int a, int b, int c, int d, int e, int f) {
	float resultNum;
	resultNum = m.m[a - 1][b - 1] * m.m[c - 1][d - 1] * m.m[e - 1][f - 1];
	return resultNum;
}

Matrix4x4 Transpose(const Matrix4x4& m) {
	Matrix4x4 resultTranspose = {};

	resultTranspose.m[0][0] = m.m[0][0];
	resultTranspose.m[0][1] = m.m[1][0];
	resultTranspose.m[0][2] = m.m[2][0];
	resultTranspose.m[0][3] = m.m[3][0];

	resultTranspose.m[1][0] = m.m[0][1];
	resultTranspose.m[1][1] = m.m[1][1];
	resultTranspose.m[1][2] = m.m[2][1];
	resultTranspose.m[1][3] = m.m[3][1];

	resultTranspose.m[2][0] = m.m[0][2];
	resultTranspose.m[2][1] = m.m[1][2];
	resultTranspose.m[2][2] = m.m[2][2];
	resultTranspose.m[2][3] = m.m[3][2];

	resultTranspose.m[3][0] = m.m[0][3];
	resultTranspose.m[3][1] = m.m[1][3];
	resultTranspose.m[3][2] = m.m[2][3];
	resultTranspose.m[3][3] = m.m[3][3];

	return resultTranspose;
}
Matrix4x4 MakeIdentity4x4() {
	Matrix4x4 resultIdentity = {};
	resultIdentity.m[0][0] = 1.0f;
	resultIdentity.m[0][1] = 0.0f;
	resultIdentity.m[0][2] = 0.0f;
	resultIdentity.m[0][3] = 0.0;

	resultIdentity.m[1][0] = 0.0f;
	resultIdentity.m[1][1] = 1.0f;
	resultIdentity.m[1][2] = 0.0f;
	resultIdentity.m[1][3] = 0.0f;

	resultIdentity.m[2][0] = 0.0f;
	resultIdentity.m[2][1] = 0.0f;
	resultIdentity.m[2][2] = 1.0f;
	resultIdentity.m[2][3] = 0.0f;

	resultIdentity.m[3][0] = 0.0f;
	resultIdentity.m[3][1] = 0.0f;
	resultIdentity.m[3][2] = 0.0f;
	resultIdentity.m[3][3] = 1.0f;

	return resultIdentity;
}

Matrix4x4 MakeTranslateMatrix(const Vector3& translate) {
	return {1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, translate.x, translate.y, translate.z, 1};
}

Matrix4x4 MakeScaleMatrix(const Vector3& scale) {
	return {scale.x, 0, 0, 0, 0, scale.y, 0, 0, 0, 0, scale.z, 0, 0, 0, 0, 1};
}

Matrix4x4 MakeRotateXMatrix(float radian) {
	float c = std::cos(radian);
	float s = std::sin(radian);
	return {1, 0, 0, 0, 0, c, s, 0, 0, -s, c, 0, 0, 0, 0, 1};
}

Matrix4x4 MakeRotateYMatrix(float radian) {
	float c = std::cos(radian);
	float s = std::sin(radian);
	return {c, 0, -s, 0, 0, 1, 0, 0, s, 0, c, 0, 0, 0, 0, 1};
}

Matrix4x4 MakeRotateZMatrix(float radian) {
	float c = std::cos(radian);
	float s = std::sin(radian);
	return {c, s, 0, 0, -s, c, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1};
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {

	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));

	Matrix4x4 resultAffine = {};
	resultAffine.m[0][0] = scale.x * rotateXYZMatrix.m[0][0];
	resultAffine.m[0][1] = scale.x * rotateXYZMatrix.m[0][1];
	resultAffine.m[0][2] = scale.x * rotateXYZMatrix.m[0][2];
	resultAffine.m[0][3] = 0;

	resultAffine.m[1][0] = scale.y * rotateXYZMatrix.m[1][0];
	resultAffine.m[1][1] = scale.y * rotateXYZMatrix.m[1][1];
	resultAffine.m[1][2] = scale.y * rotateXYZMatrix.m[1][2];
	resultAffine.m[1][3] = 0;

	resultAffine.m[2][0] = scale.z * rotateXYZMatrix.m[2][0];
	resultAffine.m[2][1] = scale.z * rotateXYZMatrix.m[2][1];
	resultAffine.m[2][2] = scale.z * rotateXYZMatrix.m[2][2];
	resultAffine.m[2][3] = 0;

	resultAffine.m[3][0] = translate.x;
	resultAffine.m[3][1] = translate.y;
	resultAffine.m[3][2] = translate.z;
	resultAffine.m[3][3] = 1;

	return resultAffine;
}

Matrix4x4 MakePerspectiveFovMatrix(float fovY, float aspectRatio, float nearClip, float farClip) {
	Matrix4x4 resultPerspectiveFov = {};

	resultPerspectiveFov.m[0][0] = (1 / aspectRatio) * (1 / std::tan(fovY / 2));
	resultPerspectiveFov.m[0][1] = 0;
	resultPerspectiveFov.m[0][2] = 0;
	resultPerspectiveFov.m[0][3] = 0;

	resultPerspectiveFov.m[1][0] = 0;
	resultPerspectiveFov.m[1][1] = (1 / std::tan(fovY / 2));
	resultPerspectiveFov.m[1][2] = 0;
	resultPerspectiveFov.m[1][3] = 0;

	resultPerspectiveFov.m[2][0] = 0;
	resultPerspectiveFov.m[2][1] = 0;
	resultPerspectiveFov.m[2][2] = farClip / (farClip - nearClip);
	resultPerspectiveFov.m[2][3] = 1;

	resultPerspectiveFov.m[3][0] = 0;
	resultPerspectiveFov.m[3][1] = 0;
	resultPerspectiveFov.m[3][2] = (-nearClip * farClip) / (farClip - nearClip);
	resultPerspectiveFov.m[3][3] = 0;

	return resultPerspectiveFov;
}
Matrix4x4 MakeOrthographicMatrix(
    float left, float top, float right, float bottom, float nearClip, float farClip) {
	Matrix4x4 resultOrthographic = {};

	resultOrthographic.m[0][0] = 2 / (right - left);
	resultOrthographic.m[0][1] = 0;
	resultOrthographic.m[0][2] = 0;
	resultOrthographic.m[0][3] = 0;

	resultOrthographic.m[1][0] = 0;
	resultOrthographic.m[1][1] = 2 / (top - bottom);
	resultOrthographic.m[1][2] = 0;
	resultOrthographic.m[1][3] = 0;

	resultOrthographic.m[2][0] = 0;
	resultOrthographic.m[2][1] = 0;
	resultOrthographic.m[2][2] = 1 / (farClip - nearClip);
	resultOrthographic.m[2][3] = 0;

	resultOrthographic.m[3][0] = (left + right) / (left - right);
	resultOrthographic.m[3][1] = (top + bottom) / (bottom - top);
	resultOrthographic.m[3][2] = nearClip / (nearClip - farClip);
	resultOrthographic.m[3][3] = 1;

	return resultOrthographic;
}
Matrix4x4 MakeViewportMatrix(
    float left, float top, float width, float height, float minDepth, float maxDepth) {
	Matrix4x4 resultViewport = {};

	resultViewport.m[0][0] = width / 2;
	resultViewport.m[0][1] = 0;
	resultViewport.m[0][2] = 0;
	resultViewport.m[0][3] = 0;

	resultViewport.m[1][0] = 0;
	resultViewport.m[1][1] = -height / 2;
	resultViewport.m[1][2] = 0;
	resultViewport.m[1][3] = 0;

	resultViewport.m[2][0] = 0;
	resultViewport.m[2][1] = 0;
	resultViewport.m[2][2] = maxDepth - minDepth;
	resultViewport.m[2][3] = 0;

	resultViewport.m[3][0] = left + width / 2;
	resultViewport.m[3][1] = top + height / 2;
	resultViewport.m[3][2] = minDepth;
	resultViewport.m[3][3] = 1;

	return resultViewport;
}