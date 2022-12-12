#include "SpherePrimitive.h"

SpherePrimitive::SpherePrimitive(RigidBody* _rigidbody) : Primitive(_rigidbody) {
	radius = _rigidbody->getMaxDim() / 2.0f;
}

float* SpherePrimitive::getDim() {
	// return xmin, xmax, ymin, ymax, zmin, zmax
	float dim[6];

	dim[0] = this->getPosition().getX() - radius; //xmin
	dim[1] = this->getPosition().getX() + radius; //xmax
	dim[2] = this->getPosition().getY() - radius; //ymin
	dim[3] = this->getPosition().getY() + radius; //ymax
	dim[4] = this->getPosition().getZ() - radius; //zmin
	dim[5] = this->getPosition().getZ() + radius; //zmax

	return dim;
}

float SpherePrimitive::getRadius() {
	return radius;
}

vector<CollisionData> SpherePrimitive::evaluateCollision(Primitive* _other)
{
	return vector<CollisionData>();
}