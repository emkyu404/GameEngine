#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K1 1 
#define DEFAULT_VALUE_K2 2

class ParticleDrag : public ParticleForceGenerator
{
private:

	float m_k1; 
	float m_k2; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	ParticleDrag(); 
	ParticleDrag(float, float); 

	/*-------------- METHODES --------------*/

	void UpdateForce(Particle* particle, float duration);

};