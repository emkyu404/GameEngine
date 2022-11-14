#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K1 0.1
#define DEFAULT_VALUE_K2 0.1

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

	void updateForce(Particle* particle, float duration);

};