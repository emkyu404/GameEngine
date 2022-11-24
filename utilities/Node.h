#pragma once

#include "Vector3D.hpp"
#include "RigidBody.h"
#include <vector>

using namespace std;

class Node {

private:

	// Values for axis x, y, z
	Vector3D center;
	float halfWidth;
	Node* childs[8];
	vector<RigidBody*> listObjects;

public:

	/*-------------- CONSTRUCTORS --------------*/

	Node();

	/*-------------- GETTERS --------------*/
};