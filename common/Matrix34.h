#pragma once
#include "Vector3D.hpp"
#include "Quaternion.h"

//const float DEFAULT_VALUES[12] = { 0 };

class Matrix34 {

private :

	float values[12];

public:
	
	/*-------------- CONSTRUCTORS --------------*/

	Matrix34();
	Matrix34(float _values[12]);

	/*-------------- OPERATORS --------------*/

	Matrix34 operator*(Matrix34 &_vector);
	Vector3D operator*(Vector3D &_vector);
	void operator = (Matrix34 _matrix);

	/*-------------- GETTERS --------------*/

	Matrix34 getInverse();
	float getDeterminant();
	float* getValues();

	/*-------------- FUNCTIONS --------------*/

	Vector3D transformPosition(Vector3D &_vector);
	Vector3D transformDirection(Vector3D& _vector);

	void setOrientationAndPosition(Quaternion& _quaternion, Vector3D& _vector);
	void invert();
	
	/*-------------- DISPLAY --------------*/

	void printMatrix34();
};

