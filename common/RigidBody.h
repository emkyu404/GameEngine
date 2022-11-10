#pragma once
#include "PhysicObject.h"
#include "Vector3D.hpp"
#include "Matrix34.h"
#include "Quaternion.h"
#include "Matrix33.h"


#define DEFAULT_VALUE_WEIGHT 1.0f
#define DEFAULT_VALUE_DAMPING 1.0f

class RigidBody : public PhysicObject
{

private:
	// Angular velocity of the rigid body
	Vector3D rotation;

	//Angular orientation of the rigid body in world space
	Quaternion orientation;

	// calculate transform matrix from orientation and rotation
	Matrix34 transformMatrix;

	// 
	Matrix33 inverseInertiaTensor;

	//same as linear damping but for rotation
	float angularDamping;

	//Accumulated torque, added by Force Generator
	Vector3D torqueAccumulator;


public:

	/*-------------- CONSTRUCTORS --------------*/
	RigidBody();
	RigidBody(Vector3D position);
	RigidBody(Vector3D position, Vector3D velocity, Vector3D acceleration);
	RigidBody(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass);
	RigidBody(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float damping);

	/*-------------- METHODES --------------*/
	void integrate(float _deltaTime);
	void reset();
	void addForce(Vector3D _newForce);  //Add force to the center of mass
	void addForceAtPoint(Vector3D _newForce, Vector3D _worldPoint);//Add force at a point in world coordinate, gerate force and torque
	void addForceAtBodyPoint(Vector3D _newForce, Vector3D _localPoint); //Add force at a point in local coordinate, point is converted in world coodinated using the transform matrix

	void clearAccumulator();

private:
	void calculateDerivedData();
	void clearForce();
	void clearTorque();
	void setInertiaTensor(Matrix33 _inertiaTensor);
	static void _calculateTransformMatrix(Matrix34& _transformMatrix, Vector3D& _position, Quaternion& _orientation);
	static void _transformInertiaTensor(Matrix33& _iitWorld, Quaternion& _orientation, Matrix33& _iitbody, Matrix34& _transformMatrix);
};