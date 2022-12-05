#include "Matrix34.h"

/*-------------- CONSTRUCTORS --------------*/

Matrix34::Matrix34() {
	identity();
}

Matrix34::Matrix34(float _values[12]) {
	for (int i = 0; i < 12; i++) {
		values[i] = _values[i];
	}
}

/*-------------- OPERATORS --------------*/

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

void Matrix34::operator = (Matrix34 _matrix) {
	for (int i = 0; i < 12; i++) {
		values[i] = _matrix.getValues()[i];
	}
}

void Matrix34::operator *= (Matrix34 _matrix) {
	(*this) = (*this) * _matrix;
}

/*-------------- GETTERS --------------*/
	
Matrix34 Matrix34::getInverse() {
	float newValues[12]; 
	// inverse only for square matrix
	// last row is [0 0 0 1], so we only used values[15] = 1

	float det = getDeterminant();
	if (det == 0) return Matrix34();;
	float invd = 1.0f / det;

	newValues[0] = (-values[9] * values[6] + values[5] * values[10]) * invd;
	newValues[1] = (values[9] * values[2] - values[1] * values[10]) * invd;
	newValues[2] = (-values[5] * values[2] + values[1] * values[6]) * invd;
	newValues[3] = (values[9] * values[6] * values[3] 
					- values[5] * values[10] * values[3]
					- values[9] * values[2] * values[7]
					+ values[1] * values[10] * values[7]
					+ values[5] * values[2] * values[11]
					- values[1] * values[6] * values[11]) * invd;

	newValues[4] = (values[8] * values[6] - values[4] * values[10]) * invd;
	newValues[5] = (-values[8] * values[2] + values[0] * values[10]) * invd;
	newValues[6] = (values[4] * values[2] - values[0] * values[6]) * invd;
	newValues[7] = (-values[8] * values[6] * values[3]
					+ values[4] * values[10] * values[3]
					+ values[8] * values[2] * values[7]
					- values[0] * values[10] * values[7]
					- values[4] * values[2] * values[11]
					+ values[0] * values[6] * values[11]) * invd;

	newValues[8] = (-values[8] * values[5] + values[4] * values[9]) * invd;
	newValues[9] = (values[8] * values[1] - values[0] * values[9]) * invd;
	newValues[10] = (-values[4] * values[1] + values[0] * values[5]) * invd;
	newValues[11] = (values[8] * values[5] * values[3]
					- values[4] * values[9] * values[3]
					- values[8] * values[1] * values[7]
					+ values[0] * values[9] * values[7]
					+ values[4] * values[1] * values[11]
					- values[0] * values[5] * values[11]) * invd;

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

Matrix33 Matrix34::getMatrixRotation() {
	float newValues[9] = { values[0], values[1], values[2],
						values[4], values[5], values[6],
						values[8], values[9], values[10] };
	return Matrix33(newValues);
}

/*-------------- FUNCTIONS --------------*/

// transform a position with the translation
Vector3D Matrix34::transformPosition(Vector3D& _vector) {
	return Vector3D(
		_vector.getX() + values[3],
		_vector.getY() + values[7],
		_vector.getZ() + values[11]);
}

// transform a direction by ignoring the translation
Vector3D Matrix34::transformDirection(Vector3D& _vector) {
	return Vector3D(
		_vector.getX() * values[0] + _vector.getY() * values[1] + _vector.getZ() * values[2],
		_vector.getX() * values[4] + _vector.getY() * values[5] + _vector.getZ() * values[6],
		_vector.getX() * values[8] + _vector.getY() * values[9] + _vector.getZ() * values[10]);
}

Vector3D Matrix34::transformAll(Vector3D& _vector) {
	return (*this) * _vector;
}

//Transform our matrix into identity matrix 34
void Matrix34::identity()
{
	values[0] = 1;
	values[1] = 0;
	values[2] = 0;
	values[3] = 0;

	values[4] = 0;
	values[5] = 1;
	values[6] = 0;
	values[7] = 0;

	values[8] = 0;
	values[9] = 0;
	values[10] = 1;
	values[11] = 0;
}

// Set this matrix to be the rotation matrix corresponding to the given quaternion
void Matrix34::setOrientationAndPosition(Quaternion &_quaternion, Vector3D &_vector) {
	values[0] = 1 - (2 * _quaternion.getJ() * _quaternion.getJ() + 2 * _quaternion.getK() * _quaternion.getK());
	values[1] = 2 * _quaternion.getI() * _quaternion.getJ() + 2 * _quaternion.getK() * _quaternion.getW();
	values[2] = 2 * _quaternion.getI() * _quaternion.getK() - 2 * _quaternion.getJ() * _quaternion.getW();
	values[3] = _vector.getX();

	values[4] = 2 * _quaternion.getI() * _quaternion.getJ() - 2 * _quaternion.getK() * _quaternion.getW();
	values[5] = 1 - (2 * _quaternion.getI() * _quaternion.getI() + 2 * _quaternion.getK() * _quaternion.getK());
	values[6] = 2 * _quaternion.getJ() * _quaternion.getK() + 2 * _quaternion.getI() * _quaternion.getW();
 	values[7] = _vector.getY();

	values[8] = 2 * _quaternion.getI() * _quaternion.getK() + 2 * _quaternion.getJ() * _quaternion.getW();
	values[9] = 2 * _quaternion.getJ() * _quaternion.getK() - 2 * _quaternion.getI() * _quaternion.getW();
	values[10] = 1 - (2 * _quaternion.getI() * _quaternion.getI() + 2 * _quaternion.getJ() * _quaternion.getJ());
	values[11] = _vector.getZ();
}

void Matrix34::invert() {
	(*this) = getInverse();
}

/*-------------- DISPLAY --------------*/

void Matrix34::printMatrix34() {
	cout << "Matrix 3x4 : \n";
	for (int i = 0; i < 12; i++) {
		cout << "[" << values[i] << "]";
		if ((i + 1) % 4 == 0) {
			cout << "\n";
		}
	}
}