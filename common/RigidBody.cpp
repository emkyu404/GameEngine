#include "RigidBody.h"

void RigidBody::integrate(float _deltaTime) {
	//1 - Update position
	position = position + velocity * _deltaTime;

	//2 - Update orientation
	Quaternion w = Quaternion(0, rotation.getX(), rotation.getY(), rotation.getZ()); // convert rotation into new quaternion ?
	//orientation = orientation +  orientation * w * (_deltaTime / 2) ; // * w ?

	//3 - Compute transform matrix & I ^ -1
	calculateDerivedData();

	//4 - Compute linear acceleration
	acceleration = forceAccumulator * this->getInverseMass();

	//5 - Compute angular acceleration


	//6 - Update linear velocity
	velocity = velocity * damping + acceleration * _deltaTime;
	//7 - Update angular velocity
	rotation = rotation * angularDamping; // + angularAcceleration * _deltaTime;

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
	Vector3D pt = _worldPoint - position; 
	forceAccumulator = forceAccumulator + _newForce;
	torqueAccumulator = torqueAccumulator + pt ^ _newForce;
}

void RigidBody::addForceAtBodyPoint(Vector3D _newForce, Vector3D _localPoint) {
	//TODO convert local position to world position and then call addForceAtPoint
}

void RigidBody::clearAccumulator() {
	clearForce();
	clearTorque();
}

void RigidBody::setInertiaTensor(Matrix33 _inertiaTensor) {
	inverseInertiaTensor = _inertiaTensor.getInverse();
}

void RigidBody::_calculateTransformMatrix(Matrix34& _transformMatrix, Vector3D& _position, Quaternion& _orientation){
	_transformMatrix.setOrientationAndPosition(_orientation, _position);
}

void RigidBody::_transformInertiaTensor(Matrix33& _iitWorld, const Quaternion& _orientation, const Matrix33& _iitbody, const Matrix34& _transformMatrix) {
}

void RigidBody::calculateDerivedData(){
	orientation.normalized();
	//TODO calculate transform matrix based on position, oritentation
	_calculateTransformMatrix(transformMatrix,position,orientation);

	//TODO calculate inertia Tensor in world coordinate
	//Cuboid inertia tensor
	const float values[9] = { (1 / 12) * getMass() * 2, 0, 0,
							0, (1 / 12) * getMass() * 2, 0,
							0, 0 , (1 / 12)* getMass() * 2 };

	Matrix33 inertiaTensor = Matrix33(values);
	setInertiaTensor(inertiaTensor);
}

void RigidBody::clearForce() {
	forceAccumulator = Vector3D();
}

void RigidBody::clearTorque() {
	torqueAccumulator = Vector3D();
}

