#pragma once
#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K 1
#define DEFAULT_VALUE_RESTLENGTH 2

class AnchoredSpringForceGenerator : public ObjectForceGenerator
{
private:

	// other anchor
	Vector3D* m_anchor;

	// Spring constants
	float m_k;
	float m_restLength;

public:

	/*-------------- CONSTRUCTORS --------------*/

	AnchoredSpringForceGenerator(Vector3D*);
	AnchoredSpringForceGenerator(Vector3D*, float m_k, float m_restLength);

	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* physicObject, float duration);

};