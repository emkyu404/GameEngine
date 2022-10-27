#include "Matrix33.h"

Matrix33::Matrix33() : Matrix33(DEFAULT_VALUES) {
}

Matrix33::Matrix33(const float _values[9]) {
	for (int i = 0; i < 9; i++) {
		values[i] = _values[i];
	}
}

Matrix33 Matrix33::operator * (Matrix33 &_otherMatrix) {
	float newValues[9] = { 
		values[0] * _otherMatrix.getValues()[0] + values[1] * _otherMatrix.getValues()[3] + values[2] * _otherMatrix.getValues()[6],
		values[0] * _otherMatrix.getValues()[1] + values[1] * _otherMatrix.getValues()[4] + values[2] * _otherMatrix.getValues()[7],
		values[0] * _otherMatrix.getValues()[2] + values[1] * _otherMatrix.getValues()[5] + values[2] * _otherMatrix.getValues()[8],

		values[3] * _otherMatrix.getValues()[0] + values[4] * _otherMatrix.getValues()[3] + values[5] * _otherMatrix.getValues()[6],
		values[3] * _otherMatrix.getValues()[1] + values[4] * _otherMatrix.getValues()[4] + values[5] * _otherMatrix.getValues()[7],
		values[3] * _otherMatrix.getValues()[2] + values[4] * _otherMatrix.getValues()[5] + values[5] * _otherMatrix.getValues()[8],

		values[6] * _otherMatrix.getValues()[0] + values[7] * _otherMatrix.getValues()[3] + values[8] * _otherMatrix.getValues()[6],
		values[6] * _otherMatrix.getValues()[1] + values[7] * _otherMatrix.getValues()[4] + values[8] * _otherMatrix.getValues()[7],
		values[6] * _otherMatrix.getValues()[2] + values[7] * _otherMatrix.getValues()[5] + values[8] * _otherMatrix.getValues()[8]
	};
	return Matrix33(newValues);
}

Vector3D Matrix33::operator * (Vector3D &_vector) {
	return Vector3D(
		_vector.getX() * values[0] + _vector.getY() * values[1] + _vector.getZ() * values[2],
		_vector.getX() * values[3] + _vector.getY() * values[4] + _vector.getZ() * values[5],
		_vector.getX() * values[6] + _vector.getY() * values[7] + _vector.getZ() * values[8]);
}

void Matrix33::operator = (Matrix33& _matrix) {
	for (int i = 0; i < 9; i++) {
		values[i] = _matrix.getValues()[i];
	}
}

/* Transform the given vector by this matrix */
Vector3D Matrix33::transform(Vector3D &_vector) {
	return (*this) * _vector;
}

Matrix33 Matrix33::getInverse() {
	float valuesInverse[9];

	float v1 = values[0] * values[4];
	float v2 = values[0] * values[5];
	float v3 = values[1] * values[3];
	float v4 = values[2] * values[3];
	float v5 = values[1] * values[6];
	float v6 = values[2] * values[6];

	float det = (v1 * values[8] - v2 * values[7] - v3 * values[8] +
		v4 * values[7] + v5 * values[5] - v6 * values[4]);
	if (det == 0.0f) return;
	float invd = 1.0f / det;

	valuesInverse[0] = (values[4] * values[8] - values[5] * values[7]) * invd;
	valuesInverse[1] = -(values[1] * values[8] - values[2] * values[7]) * invd;
	valuesInverse[2] = (values[1] * values[5] - values[2] * values[4]) * invd;
	valuesInverse[3] = -(values[3] * values[8] - values[5] * values[6]) * invd;
	valuesInverse[4] = (values[0] * values[8] - v6) * invd;
	valuesInverse[5] = -(v2 - v4) * invd;
	valuesInverse[6] = (values[3] * values[7] - values[4] * values[6]) * invd;
	valuesInverse[7] = -(values[0] * values[7] - v5) * invd;
	valuesInverse[8] = (v1 - v3) * invd;

	return Matrix33(valuesInverse);
}

float* Matrix33::getValues() {
	return values;
}

void Matrix33::printMatrix33() {
	cout << "Matrix 3x3 : \n";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "[" << values[i] << "]";
		}
	}
}