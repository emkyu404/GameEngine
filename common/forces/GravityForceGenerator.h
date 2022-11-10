#pragma once

#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"


const Vector3D EARTH_GRAVITY = Vector3D(0, -10.0f, 0); 

class GravityForceGenerator : public ObjectForceGenerator
{
private:

	Vector3D m_gravity; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	GravityForceGenerator(); 
	GravityForceGenerator(Vector3D); 

	/*-------------- METHODES --------------*/
	
	void updateForce(PhysicObject* object, float duration); 

};