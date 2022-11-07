#pragma once

#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K 1
#define DEFAULT_VALUE_RESTLENGTH 3 //changed so by default particles are in rest position

class SpringForceGenerator : public ObjectForceGenerator
{
private:

	// other anchor
	PhysicObject* m_other;

	// Spring constants
	float m_k; 
	float m_restLength; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	SpringForceGenerator(PhysicObject*);
	SpringForceGenerator(PhysicObject*, float m_k, float m_restLength);

	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* particle, float duration);

};