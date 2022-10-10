#pragma once

#include <stdlib.h>
#include <math.h>
#include<iostream>

using namespace std;

class Vector3D {

private:

	// Values for axis x, y, z
	float x, y, z;

public:

	/*-------------- CONSTRUCTORS --------------*/

	Vector3D();
	Vector3D(float _X, float _Y, float _Z);

	/*-------------- GETTERS --------------*/

	Vector3D* getVector3D();
	float getX();
	float getY();
	float getZ();

	/*-------------- SETTERS --------------*/

	void setVector3D(float _X, float _Y, float _Z);
	void setX(float _X);
	void setY(float _Y);
	void setZ(float _Z);

	/*-------------- OPERATORS --------------*/

	Vector3D operator + (Vector3D _vector);
	Vector3D operator - (Vector3D _vector);
	Vector3D operator * (float _scalar);
	Vector3D operator / (float _scalar);
	void operator = (Vector3D _vector);
	Vector3D operator ^ (Vector3D _vector);
	float operator & (Vector3D _vector);
	Vector3D operator += (Vector3D _vector);
	Vector3D operator -= (Vector3D _vector);

	/*-------------- METHODES --------------*/

	void invert();
	bool isEquals(Vector3D _vector);
	float norm();
	float norm(Vector3D _vector);
	Vector3D normalize();
	void clear();
	Vector3D cross(Vector3D _vector); //return cross product between two vectors

	/*-------------- PRINTS --------------*/

	void print();

};
