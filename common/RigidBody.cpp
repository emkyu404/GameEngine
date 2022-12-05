#include "RigidBody.h"


/*-------------- CONSTRUCTORS --------------*/



RigidBody::RigidBody() : RigidBody(Vector3D(0,0,0)) {
}

RigidBody::RigidBody(Vector3D _position) : RigidBody(_position, Vector3D(1,1,1)) {
}

RigidBody::RigidBody(Vector3D _position, Vector3D _scale) : RigidBody(_position, _scale, DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING) {
}

RigidBody::RigidBody(Vector3D _position, Vector3D _scale, float _inverseMass, float _damping) {
	position = _position;
	initialPosition = position;
	velocity = Vector3D();
	acceleration = Vector3D();
	inverseMass = _inverseMass;
	damping = _damping;
	forceAccumulator = Vector3D();
	orientation = Quaternion();
	angularDamping = DEFAULT_VALUE_ANGULARDAMPING;
	angularAcceleration = Vector3D();
	objectScale = _scale;

	// Half size based on scale
	float dx, dy, dz;
	dx = _scale.getX();  dy = _scale.getY(); dz = _scale.getY();

	float values[9] = { (1.0f / 12.0f) * getMass() * (pow(dy * 2, 2) + pow(dz * 2,2)), 0, 0,
							0, (1.0f / 12.0f) * getMass() * (pow(dx * 2, 2) + pow(dz * 2,2)), 0,
							0, 0 , (1.0f / 12.0f) * getMass() * (pow(dx * 2, 2) + pow(dy * 2,2)) };

	inverseInertiaTensor = Matrix33(values).getInverse();

	calculateDerivedData();
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
	angularAcceleration = inverseInertiaTensorWorld * torqueAccumulator;

	//6 - Update linear velocity
	velocity = velocity * pow(damping,_deltaTime) + acceleration * _deltaTime;

	//7 - Update angular velocity
	rotation = rotation * pow(angularDamping,_deltaTime) + angularAcceleration * _deltaTime;

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
	calculateDerivedData();
}

void RigidBody::addForce(Vector3D _newForce) {
	forceAccumulator = forceAccumulator + _newForce;
}

void RigidBody::addForceAtPoint(Vector3D _newForce, Vector3D _worldPoint) {

	//Compute the point relative to center of mass of the rigidbody
	Vector3D pt = _worldPoint - position; 
	forceAccumulator = forceAccumulator + _newForce;
	torqueAccumulator = torqueAccumulator + (pt ^ _newForce);
}

void RigidBody::addForceAtBodyPoint(Vector3D _newForce, Vector3D _localPoint) {
	
	//get local point in world coordinates
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

Vector3D RigidBody::getScale() {
	return objectScale;
}

void RigidBody::setOrientation(Vector3D _orientation)
{
	float roll = _orientation.getX();
	float pitch = _orientation.getY();
	float yaw = _orientation.getZ();
	// from https://en.wikipedia.org/wiki/Conversion_between_quaternions_and_Euler_angles

	float cr = cos(roll * 0.5);
	float sr = sin(roll * 0.5);
	float cp = cos(pitch * 0.5);
	float sp = sin(pitch * 0.5);
	float cy = cos(yaw * 0.5);
	float sy = sin(yaw * 0.5);

	Quaternion q;

	q.setW(cr * cp * cy + sr * sp * sy);
	q.setI(sr * cp * cy - cr * sp * sy); 
	q.setJ(cr * sp * cy + sr * cp * sy); 
	q.setK(cr * cp * sy - sr * sp * cy);
	orientation = q;
}


void RigidBody::_calculateTransformMatrix(Matrix34& _transformMatrix, Vector3D& _position, Quaternion& _orientation){
	_transformMatrix.setOrientationAndPosition(_orientation, _position);
}

void RigidBody::_transformInertiaTensor(Matrix33& _iitWorld, Quaternion& _orientation, Matrix33& _iitbody, Matrix34& _transformMatrix) {
	
	//Basis transform (rotationMatrix * iitbody) * rotationMatrix ^ -1
	Matrix33 rotationMatrix = _transformMatrix.getMatrixRotation();
	Matrix33 invRotationMatrix = rotationMatrix.getInverse();
	_iitWorld = rotationMatrix * _iitbody * invRotationMatrix;
}

void RigidBody::calculateDerivedData(){
	//Normalize orientation
	orientation.normalized();
	_calculateTransformMatrix(transformMatrix,position,orientation);
	_transformInertiaTensor(inverseInertiaTensorWorld, orientation, inverseInertiaTensor, transformMatrix);
}

void RigidBody::clearForce() {
	forceAccumulator = Vector3D();
}

void RigidBody::clearTorque() {
	torqueAccumulator = Vector3D();
}

