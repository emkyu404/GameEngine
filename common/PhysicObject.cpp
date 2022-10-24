#include "PhysicObject.h"

/*-------------- GETTERS --------------*/

// Return position 
Vector3D PhysicObject::getPosition() {
	return position;
}

// Return initial positon 
Vector3D PhysicObject::getInitialPosition() {
	return initialPosition;
}

// Return velocity 
Vector3D PhysicObject::getVelocity() {
	return velocity;
}

// Return acceleration 
Vector3D PhysicObject::getAcceleration() {
	return acceleration;
}

// Return weight 
float PhysicObject::getMass() {
	return 1.0f / inverseMass;
}

// Return inverse weight 
float PhysicObject::getInverseMass() {
	return inverseMass;
}


/*-------------- SETTERS --------------*/

// Set Vector3 position 
void PhysicObject::setPosition(Vector3D _position) {
	position = _position;
}

void PhysicObject::initializePosition(Vector3D _initialPosition) {
	position = _initialPosition;
	initialPosition = _initialPosition;
}

// Set Vector3 velocity
void PhysicObject::setVelocity(Vector3D _velocity) {
	velocity = _velocity;
}

// Set Vector3 acceleration
void PhysicObject::setAcceleration(Vector3D _acceleration) {
	acceleration = _acceleration;
}

// Set weight
void PhysicObject::setMass(float _mass) {
	inverseMass = 1.0f / _mass;
}

// Change weight to inverse weight 
void PhysicObject::setInverseMass(float _inverseMass) {
	inverseMass = _inverseMass;
}