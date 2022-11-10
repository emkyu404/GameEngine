#pragma once

#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K1 0.1
#define DEFAULT_VALUE_K2 0.1

class DragForceGenerator : public ObjectForceGenerator
{
private:

	float m_k1; 
	float m_k2; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	DragForceGenerator(); 
	DragForceGenerator(float, float); 

	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* particle, float duration);

};