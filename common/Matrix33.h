#pragma once
#include "Vector3D.hpp"
#include "Quaternion.h"

using namespace std;

//const float DEFAULT_VALUES[9] = {0};

class Matrix33 {

private:

	float values[9];

public :

	/*-------------- CONSTRUCTORS --------------*/

	Matrix33();
	Matrix33(const float _values[9]);

	/*-------------- GETTERS --------------*/

	Matrix33 getInverse();
	Matrix33 getTranspose();
	float* getValues();

	/*-------------- OPERATORS --------------*/

	Matrix33 operator * (Matrix33 &_otherMatrix);
	Vector3D operator * (Vector3D &_vector);
	void operator = (Matrix33 _matrix);

	/*-------------- METHODS --------------*/

	Vector3D transform(Vector3D &_vector);
	void setOrientation(Quaternion& _quaternion);
	void invert();
	void transpose();

	/*-------------- DISPLAY --------------*/

	void printMatrix33();

};

