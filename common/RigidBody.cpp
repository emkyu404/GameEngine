#include "RigidBody.h"


/*-------------- CONSTRUCTORS --------------*/

// Default constructor
RigidBody::RigidBody()
	: RigidBody(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT)
{
}

// Default constructor with position
RigidBody::RigidBody(Vector3D _position)
	: RigidBody(_position, Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING)
{
}

// Default constructor with basic vectors 
RigidBody::RigidBody(Vector3D _position, Vector3D _velocity, Vector3D _acceleration)
	: RigidBody(_position, _velocity, _acceleration, DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING)
{
}

// Default constructor with basic vectors and weight 
RigidBody::RigidBody(Vector3D _position, Vector3D _velocity, Vector3D _acceleration, float _inverseMass)
	: RigidBody(_position, _velocity, _acceleration, _inverseMass, DEFAULT_VALUE_DAMPING)
{
}

// Full customization constructor
RigidBody::RigidBody(Vector3D _position, Vector3D _velocity, Vector3D _acceleration, float _inverseMass, float _damping) {
	position = _position;
	initialPosition = position;
	velocity = _velocity;
	acceleration = _acceleration;
	inverseMass = _inverseMass;
	damping = _damping;
	forceAccumulator = Vector3D();
	orientation = Quaternion();
	angularDamping = DEFAULT_VALUE_ANGULARDAMPING;
	angularAcceleration = Vector3D();
}


void RigidBody::integrate(float _deltaTime) {
	//1 - Update position
	position = position + velocity * _deltaTime;

	//2 - Update orientation
	orientation.updateByAngularVelocity(rotation, _deltaTime);

	//3 - Compute transform matrix & I ^ -1
	calculateDerivedData();

	//4 - Compute linear acceleration
	acceleration = forceAccumulator * this->getInverseMass();

	//5 - Compute angular acceleration
	angularAcceleration = inverseInertiaTensor * torqueAccumulator;

	//6 - Update linear velocity
	velocity = velocity * damping + acceleration * _deltaTime;
	//7 - Update angular velocity
	rotation = rotation * angularDamping + angularAcceleration * _deltaTime;

	//8 - Clear accumulators
	clearAccumulator();
}

void RigidBody::reset() {
	position = initialPosition;
	velocity = Vector3D();
	acceleration = Vector3D();
	orientation = Quaternion();
	rotation = Vector3D();
	angularAcceleration = Vector3D();
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
	Vector3D pt = transformMatrix.transformAll(_localPoint);
	addForceAtPoint(_newForce, pt);
}

Quaternion RigidBody::getOrientation()
{
	return orientation;
}

void RigidBody::clearAccumulator() {
	clearForce();
	clearTorque();
}

Matrix34 RigidBody::getTransformMatrix()
{
	return transformMatrix;
}

Vector3D RigidBody::getTorque()
{
	return rotation;
}

Vector3D RigidBody::getAngularAcceleration() {
	return angularAcceleration;
}

void RigidBody::setInertiaTensor(Matrix33 _inertiaTensor) {
	inverseInertiaTensor = _inertiaTensor.getInverse();
}

void RigidBody::_calculateTransformMatrix(Matrix34& _transformMatrix, Vector3D& _position, Quaternion& _orientation){
	_transformMatrix.setOrientationAndPosition(_orientation, _position);
}

void RigidBody::_transformInertiaTensor(Matrix33& _iitWorld, Quaternion& _orientation, Matrix33& _iitbody, Matrix34& _transformMatrix) {
	
	//Basis transform (rotationMatrix * iitbody) * rotationMatrix
	Matrix33 rotationMatrix = _transformMatrix.getMatrixRotation();
	_iitWorld = rotationMatrix.getInverse() * _iitbody * rotationMatrix;
}

void RigidBody::calculateDerivedData(){
	orientation.normalized();
	_calculateTransformMatrix(transformMatrix,position,orientation);

	// Hardset of inertia tensor of cuboœd, dy = 2 and dz = 2
	float dy, dz;
	dy = 2; dz = 2;

	float values[9] = { (1.0f / 12.0f) * getMass() * (pow(dy, 2) + pow(dz,2)), 0, 0,
							0, (1.0f / 12.0f) * getMass() * (pow(dy, 2) + pow(dz,2)), 0,
							0, 0 , (1.0f / 12.0f)* getMass() * (pow(dy, 2) + pow(dz,2)) };

	Matrix33 inverseInertiaTensorBody = Matrix33(values).getInverse();
	_transformInertiaTensor(inverseInertiaTensor, orientation, inverseInertiaTensorBody, transformMatrix);
}

void RigidBody::clearForce() {
	forceAccumulator = Vector3D();
}

void RigidBody::clearTorque() {
	torqueAccumulator = Vector3D();
}

