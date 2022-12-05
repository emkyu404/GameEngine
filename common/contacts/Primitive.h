#pragma once
#include "RigidBody.h"
#include "CollisionData.h"
#include <vector>
#include "Vector3D.hpp"

class Primitive {

protected:
	RigidBody* rigidbody; //reference to rigidbody
	Matrix34 offset; //position relative to rigidbody ?

public:
	Primitive(RigidBody* _rigidBody);
	Primitive(RigidBody* _rigidBody, Matrix34 _offset);
	Vector3D getPosition();
	virtual vector<CollisionData> evaluateCollision(Primitive* _other) = 0;
};