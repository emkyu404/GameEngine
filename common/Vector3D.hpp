#ifndef VECTOR3D_H
#define VECTOR3D_H


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
	Vector3D(float X, float Y, float Z);

	/*-------------- GETTERS --------------*/

	Vector3D* getVector3D();
	float getX();
	float getY();
	float getZ();

	/*-------------- SETTERS --------------*/

	void setVector3D(float X, float Y, float Z);
	void setX(float X);
	void setY(float Y);
	void setZ(float Z);

	/*-------------- OPERATORS --------------*/

	Vector3D operator + (Vector3D vector);
	Vector3D operator - (Vector3D vector);
	Vector3D operator * (float scalar);
	Vector3D operator / (float scalar);
	void operator = (Vector3D Vector);
	Vector3D operator ^ (Vector3D vector);
	float operator & (Vector3D vector);

	/*-------------- METHODES --------------*/

	void invert();
	bool isEquals(Vector3D vector);
	float norm();
	Vector3D normalize();

	/*-------------- PRINTS --------------*/

	void print();

};
#endif