#include "Matrix33.h"

/*-------------- CONSTRUCTORS --------------*/

Matrix33::Matrix33() : Matrix33(DEFAULT_VALUES) {
}

Matrix33::Matrix33(const float _values[9]) {
	for (int i = 0; i < 9; i++) {
		values[i] = _values[i];
	}
}

/*-------------- OPERATORS --------------*/

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

void Matrix33::operator = (Matrix33 _matrix) {
	for (int i = 0; i < 9; i++) {
		values[i] = _matrix.getValues()[i];
	}
}

/*-------------- GETTERS --------------*/

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
	if (det == 0.0f) return Matrix33(DEFAULT_VALUES);
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

Matrix33 Matrix33::getTranspose() {
	float newValues[9];

	newValues[0] = values[0];
	newValues[1] = values[3];
	newValues[2] = values[6];
	newValues[3] = values[1];
	newValues[4] = values[4];
	newValues[5] = values[7];
	newValues[6] = values[2];
	newValues[7] = values[5];
	newValues[8] = values[8];

	return Matrix33(newValues);
}

float* Matrix33::getValues() {
	return values;
}

/*-------------- FUNCTIONS --------------*/

/* Transform the given vector by this matrix */
Vector3D Matrix33::transform(Vector3D& _vector) {
	return (*this) * _vector;
}

// Set this matrix to be the rotation matrix corresponding to the given quaternion
void Matrix33::setOrientation(Quaternion& _quaternion) {
	values[0] = 1 - (2*_quaternion.getJ() * _quaternion.getJ() + 2*_quaternion.getK() * _quaternion.getK());
	values[1] = 2 * _quaternion.getI() * _quaternion.getJ() + 2 * _quaternion.getK() * _quaternion.getW();
	values[2] = 2 * _quaternion.getI() * _quaternion.getK() - 2 * _quaternion.getJ() * _quaternion.getW();
	values[3] = 2 * _quaternion.getI() * _quaternion.getJ() - 2 * _quaternion.getK() * _quaternion.getW();
	values[4] = 1 - (2 * _quaternion.getI() * _quaternion.getI() + 2 * _quaternion.getK() * _quaternion.getK());
	values[5] = 2 * _quaternion.getJ() * _quaternion.getK() + 2 * _quaternion.getI() * _quaternion.getW();
	values[6] = 2 * _quaternion.getI() * _quaternion.getK() + 2 * _quaternion.getJ() * _quaternion.getW();
	values[7] = 2 * _quaternion.getJ() * _quaternion.getK() - 2 * _quaternion.getI() * _quaternion.getW();
	values[8] = 1 - (2 * _quaternion.getI() * _quaternion.getI() + 2 * _quaternion.getJ() * _quaternion.getJ());
}

void Matrix33::invert() {
	(*this) = getInverse();
}

void Matrix33::transpose() {
	(*this) = getTranspose();
}

/*-------------- DISPLAY --------------*/

void Matrix33::printMatrix33() {
	cout << "Matrix 3x3 : \n";
	for (int i = 0; i < 9; i++) {
		for (int j = 0; j < 3; j++) {
			cout << "[" << values[i] << "]";
		}
	}
}