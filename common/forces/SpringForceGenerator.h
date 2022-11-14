#pragma once

#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K 1
#define DEFAULT_VALUE_RESTLENGTH 3 //changed so by default particles are in rest position

class SpringForceGenerator : public ObjectForceGenerator
{
protected:
	// Spring constants
	float m_k;
	float m_restLength;

public:

	/*-------------- CONSTRUCTORS --------------*/
	SpringForceGenerator();
	SpringForceGenerator(float m_k, float m_restLength);

	/*-------------- METHODES --------------*/

	virtual void updateForce(PhysicObject*, float duration) = 0;
};