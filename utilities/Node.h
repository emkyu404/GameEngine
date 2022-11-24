#pragma once

#include "Vector3D.hpp"
#include "RigidBody.h"
#include <vector>

#define DEFAULT_HALF_WIDTH 5

using namespace std;

class Node {

private:

	Vector3D center;
	float halfWidth;
	Node* childs[8];
	bool hasObjects; 
	
	vector<RigidBody*> listStudiedRigibodies; 
	vector<RigidBody*> listConsideredRigidBodies;

public:

	/*-------------- CONSTRUCTORS --------------*/

	Node();
	Node(float halfWidth);
	Node(Node* parent, Vector3D center); 

	/*-------------- GETTERS --------------*/

	Vector3D getCenter();
	float getHalfWidth();
	Node** getChilds();
	bool hasObjectsInIt(); 

	vector<RigidBody*> getListStudiedRigidbodies();
	vector<RigidBody*> getListConsideredRigidbodies();


	/*-------------- SETTERS --------------*/

	void setCenter(Vector3D);
	void setHalfWidth(float);
	void setListStudiedRigidbodies(vector<RigidBody*>);

	/*-------------- METHODS --------------*/

	bool getObjectInIt();
	void createChilds(); 
}
