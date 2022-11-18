#include "SimpleForceGenerator.h"
#include "RigidBody.h"

SimpleForceGenerator::SimpleForceGenerator() : SimpleForceGenerator(Vector3D(), Vector3D()) {
}

SimpleForceGenerator::SimpleForceGenerator(Vector3D _force) : SimpleForceGenerator(_force, Vector3D()) {
}

SimpleForceGenerator::SimpleForceGenerator(Vector3D _force, Vector3D _localBodyPoint) {
	this->force = _force;
	this->localBodyPoint = _localBodyPoint;
}

void SimpleForceGenerator::updateForce(PhysicObject* _object, float _duration) {
	//if rigidbody -> cast rigidbody
	if(dynamic_cast<RigidBody*>(_object) != nullptr){
		RigidBody* rigidbody = dynamic_cast<RigidBody*>(_object);
		rigidbody->addForceAtBodyPoint(force, localBodyPoint);
	}
	else {
		_object->addForce(force);
	}
}