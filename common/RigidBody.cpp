#include "RigidBody.h"

void RigidBody::integrate(float _deltaTime) {
	acceleration = forceAccumulator * inverseMass;
	velocity = velocity * damping + acceleration * _deltaTime;
	position = position + velocity * _deltaTime;
	clearForce();
}

void RigidBody::reset() {
	position = initialPosition;
	velocity = Vector3D();
	acceleration = Vector3D();
}

void RigidBody::addForce(Vector3D _newForce) {
	forceAccumulator = forceAccumulator + _newForce;
}

void RigidBody::clearForce() {
}
