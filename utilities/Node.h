#pragma once

#include "Vector3D.hpp"
#include "RigidBody.h"

using namespace std;

class Node {

private:

	// Values for axis x, y, z
	Vector3D center; 
	int key; 
	int hasChild; 
	RigidBody* listObjects; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	Node();

	/*-------------- GETTERS --------------*/