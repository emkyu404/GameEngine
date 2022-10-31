#include "Matrix34.h"

Matrix34::Matrix34() : Matrix34(DEFAULT_VALUES) {
}

Matrix34::Matrix34(const float _values[12]) {
	for (int i = 0; i < 12; i++) {
		values[i] = _values[i];
	}
}

Matrix34 Matrix34::operator* (Matrix34& _otherMatrix) {
	float newValues[12] = {
		_otherMatrix.getValues()[0] * values[0] + _otherMatrix.getValues()[4] * values[1] + _otherMatrix.getValues()[8] * values[2],
		_otherMatrix.getValues()[1] * values[0] + _otherMatrix.getValues()[5] * values[1] + _otherMatrix.getValues()[9] * values[2],
		_otherMatrix.getValues()[2] * values[0] + _otherMatrix.getValues()[6] * values[1] + _otherMatrix.getValues()[10] * values[2],
		_otherMatrix.getValues()[3] * values[0] + _otherMatrix.getValues()[7] * values[1] + _otherMatrix.getValues()[11] * values[2] + values[3],

		_otherMatrix.getValues()[0] * values[4] + _otherMatrix.getValues()[4] * values[5] + _otherMatrix.getValues()[8] * values[6],
		_otherMatrix.getValues()[1] * values[4] + _otherMatrix.getValues()[5] * values[5] + _otherMatrix.getValues()[9] * values[6],
		_otherMatrix.getValues()[2] * values[4] + _otherMatrix.getValues()[6] * values[5] + _otherMatrix.getValues()[10] * values[6],
		_otherMatrix.getValues()[3] * values[4] + _otherMatrix.getValues()[7] * values[5] + _otherMatrix.getValues()[11] * values[6] + values[7],

		_otherMatrix.getValues()[0] * values[8] + _otherMatrix.getValues()[4] * values[9] + _otherMatrix.getValues()[8] * values[10],
		_otherMatrix.getValues()[1] * values[8] + _otherMatrix.getValues()[5] * values[9] + _otherMatrix.getValues()[9] * values[10],
		_otherMatrix.getValues()[2] * values[8] + _otherMatrix.getValues()[6] * values[9] + _otherMatrix.getValues()[10] * values[10],
		_otherMatrix.getValues()[3] * values[8] + _otherMatrix.getValues()[7] * values[9] + _otherMatrix.getValues()[11] * values[10] + values[11]
	};

	return Matrix34(newValues);
}

Vector3D Matrix34::operator* (Vector3D& _vector) {
	return Vector3D(
		_vector.getX() * values[0] + _vector.getY() * values[1] + _vector.getZ() * values[2] + values[3],
		_vector.getX() * values[4] + _vector.getY() * values[5] + _vector.getZ() * values[6] + values[7],
		_vector.getX() * values[8] + _vector.getY() * values[9] + _vector.getZ() * values[10] + values[11]
	);
}

void Matrix34::operator= (Matrix34& _matrix) {
	for (int i = 0; i < 12; i++) {
		values[i] = _matrix.getValues()[i];
	}
}

Vector3D Matrix34::transform(Vector3D& _vector) {
	return (*this) * _vector;
}

Matrix34 Matrix34::getInverse() {
	float newValues[12];

	float det = getDeterminant();
	if (det == 0) return Matrix34(DEFAULT_VALUES);;
	float invd = 1.0f / det;
	// à finirs
	newValues[0] = -(values[9] * values[6] + values[5] * values[10]) * invd;
	newValues[1] = (values[9] * values[2] - values[1] * values[10]) * invd;
	newValues[2] = -(values[5] * values[2] + values[1] * values[10]) * invd;
	newValues[3] = (values[9] * values[6] - values[5] * values[10]) * invd;
	newValues[4] = -(values[9] * values[6] + values[5] * values[10]) * invd;
	newValues[5] = (values[9] * values[6] - values[5] * values[10]) * invd;
	newValues[6] = -(values[9] * values[6] + values[5] * values[10]) * invd;
	newValues[7] = (values[9] * values[6] - values[5] * values[10]) * invd;
	newValues[8] = -(values[9] * values[6] + values[5] * values[10]) * invd;
	newValues[9] = (values[9] * values[6] - values[5] * values[10]) * invd;
	newValues[10] = -(values[9] * values[6] + values[5] * values[10]) * invd;
	newValues[11] = (values[9] * values[6] - values[5] * values[10]) * invd;

	return Matrix34(newValues);
}

float Matrix34::getDeterminant() {
	return values[8] * values[5] * values[2] +
		values[4] * values[9] * values[2] +
		values[8] * values[1] * values[6] -
		values[0] * values[9] * values[6] -
		values[4] * values[1] * values[10] +
		values[0] * values[5] * values[10];
}

float* Matrix34::getValues() {
	return values;
}

void Matrix34::printMatrix34() {
	cout << "Matrix 4x4 : \n";
	for (int i = 0; i < 12; i++) {
		for (int j = 0; j < 4; j++) {
			cout << "[" << values[i] << "]";
		}
	}
}