#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"


Vector3D EARTH_GRAVITY = Vector3D(0, -10.0f, 0); 

class ParticleGravity : public ParticleForceGenerator
{
private:

	Vector3D m_gravity; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	ParticleGravity(); 
	ParticleGravity(Vector3D); 

	/*-------------- METHODES --------------*/
	
	void UpdateForce(Particle* particle, float duration); 

};