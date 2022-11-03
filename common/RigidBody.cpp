#include "RigidBody.h"

void RigidBody::integrate(float _deltaTime) {
	//1 - Update position
	velocity = position + velocity * _deltaTime;
	//2 - Update orientation
	rotation = rotation +  rotation * (_deltaTime / 2); // * w ?

	//3 - Compute transform matrix & I ^ -1
	calculateDerivedData();

	//4 - Compupte liear acceleration
	acceleration = forceAccumulator * this->getInverseMass();

	//5 - Compute angular acceleration

	//6 - Update linear velocity
	acceleration = velocity * damping + acceleration * _deltaTime;
	//7 - Update angular velocity

	//8 - Clear accumulators
	clearAccumulator();
}

void RigidBody::reset() {
	position = initialPosition;
	velocity = Vector3D();
	acceleration = Vector3D();
}

void RigidBody::addForce(Vector3D _newForce) {
	forceAccumulator = forceAccumulator + _newForce;
}

void RigidBody::addForceAtPoint(Vector3D _newForce, Vector3D _worldPoint) {
	//TODO
	Vector3D pt = _worldPoint - position; //
	forceAccumulator = forceAccumulator + _newForce;
	//torqueAccumulator = torqueAccumulator + pt % _newForce;
}

void RigidBody::addForceAtBodyPoint(Vector3D _newForce, Vector3D _localPoint) {
	//TODO convert local position to world position and then call addForceAtPoint
}

void RigidBody::clearAccumulator() {
	clearForce();
	clearTorque();
}

void RigidBody::setInertiaTensor(Matrix33 _inertiaTensor) {
	//inverseInertiaTensor = _inertiaTensor.getInverse();
}

void RigidBody::calculateDerivedData(){
	orientation.normalized();
	//TODO calculate transform matrix based on position, oritentation

	//TODO calculate inertia Tensor in world coordinate
}

void RigidBody::clearForce() {
	forceAccumulator = Vector3D();
}

void RigidBody::clearTorque() {
	torqueAccumulator = Vector3D();
}

