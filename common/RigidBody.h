#pragma once
#include "PhysicObject.h"
#include "Vector3D.hpp"
#include "Matrix34.h"
#include "Quaternion.h"
#include "Matrix33.h"


#define DEFAULT_VALUE_WEIGHT 100.0f
#define DEFAULT_VALUE_DAMPING 1.0f
#define DEFAULT_VALUE_ANGULARDAMPING 1.0f;

class RigidBody : public PhysicObject
{

private:

	// Angular acceleration of the rigid body
	Vector3D angularAcceleration;

	// Angular velocity of the rigid body
	Vector3D rotation;

	//Angular orientation of the rigid body in world space
	Quaternion orientation;

	// calculate transform matrix from orientation and rotation
	Matrix34 transformMatrix;

	// local inverse inertia tensor, setup once 
	Matrix33 inverseInertiaTensor;

	// world coordinate inertia tensor, calculate each frame
	Matrix33 inverseInertiaTensorWorld;

	//same as linear damping but for rotation
	float angularDamping;

	//Accumulated torque, added by Force Generator
	Vector3D torqueAccumulator;

	//Scale of object - Describe dx, dy and dz for Cuboïd
	Vector3D objectScale;


public:

	/*-------------- CONSTRUCTORS --------------*/
	RigidBody();
	RigidBody(Vector3D position);
	RigidBody(Vector3D position, Vector3D scale);
	RigidBody(Vector3D position, Vector3D scale, float mass, float damping);

	/*-------------- METHODES --------------*/
	void integrate(float _deltaTime);
	void reset();
	void addForce(Vector3D _newForce);  //Add force to the center of mass
	void addForceAtPoint(Vector3D _newForce, Vector3D _worldPoint);//Add force at a point in world coordinate, gerate force and torque
	void addForceAtBodyPoint(Vector3D _newForce, Vector3D _localPoint); //Add force at a point in local coordinate, point is converted in world coodinated using the transform matrix

	Quaternion getOrientation();

	void clearAccumulator();

	Matrix34 getTransformMatrix();

	Vector3D getTorque();
	Vector3D getAngularAcceleration();
	Vector3D getScale();

private:
	void calculateDerivedData();
	void clearForce();
	void clearTorque();
	static void _calculateTransformMatrix(Matrix34& _transformMatrix, Vector3D& _position, Quaternion& _orientation);
	static void _transformInertiaTensor(Matrix33& _iitWorld, Quaternion& _orientation, Matrix33& _iitbody, Matrix34& _transformMatrix);
};