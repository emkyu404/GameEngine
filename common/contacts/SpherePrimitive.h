#pragma once
#include "Primitive.h"

class SpherePrimitive : public Primitive{

protected :
	float radius;

public :
	SpherePrimitive(RigidBody* _rigidBody);
	float* getDim();
	float getRadius(); 
	vector<CollisionData> evaluateCollision(Primitive* _other) override;
};

