#include "Primitive.h"


Primitive::Primitive(RigidBody* _rigidbody) : Primitive(_rigidbody, Matrix34()) {

}

Primitive::Primitive(RigidBody* _rigidBody, Matrix34 _offset) {
	rigidbody = _rigidBody;
	offset = _offset;
}

Vector3D Primitive::getPosition()
{
	return rigidbody->getPosition();
}
