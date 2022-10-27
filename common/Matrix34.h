#pragma once
#include "Vector3D.hpp"

const float DEFAULT_VALUES[12] = { 0 };

class Matrix34 {

private :

	float values[12];

public:
	
	Matrix34();
	Matrix34(const float _values[12]);

	Matrix34 operator*(Matrix34 &_vector);
	Vector3D operator*(Vector3D &_vector);
	void operator = (Matrix34& _matrix);

	Vector3D transform(Vector3D& _vector);

	Matrix34 getInverse();
	float getDeterminant();
	//void setOrientationAndPosition(Quaternion& _quaternion, Vector3D& _vector);

	Vector3D transformationPosition(Vector3D &_vector);
	Vector3D transformDirection(Vector3D& _vector);

	float* getValues();

	void printMatrix34();
};

