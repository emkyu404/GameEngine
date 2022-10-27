#pragma once
#include "Vector3D.hpp"

using namespace std;

const float DEFAULT_VALUES[9] = {0};

class Matrix33 {

private:

	float values[9];

public :

	Matrix33();
	Matrix33(const float _values[9]);

	Matrix33 operator * (Matrix33 &_otherMatrix);
	Vector3D operator * (Vector3D &_vector);
	void operator = (Matrix33 &_matrix);

	Vector3D transform(Vector3D &_vector);
	Matrix33 getInverse();
	Matrix33 getTranspose();

	//void setOrientation(const Quaternion& q);

	float* getValues();

	void printMatrix33();
};

