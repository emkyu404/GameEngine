#pragma once

#include <stdlib.h>
#include <math.h>
#include<iostream>
#include "Vector3D.hpp"

using namespace std;

class Quaternion {

private:

	// Values for axis w, i, j, k
	float values[4]; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	Quaternion(); 
	Quaternion(float w, float i, float j, float k); 

	/*-------------- GETTERS --------------*/

	Quaternion* getQuaternion(); 
	float getW(); 
	float getI(); 
	float getJ(); 
	float getK(); 

	/*-------------- SETTERS --------------*/

	void setQuaternion(float _W, float _I, float _J, float _K); 
	void setW(float); 
	void setI(float);
	void setJ(float);
	void setK(float);

	/*-------------- OPERATORS --------------*/

	Quaternion operator*(const Quaternion& other);

	/*-------------- METHODS --------------*/

	void Normalized(); 
	void rotateByVector(const Vector3D& vector); 
	void updateByAngularVelocity(const Vector3D& rotation, float duration); 

	/*-------------- DISPLAY --------------*/

	void print(); 

}; 