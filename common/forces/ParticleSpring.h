#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K 1
#define DEFAULT_VALUE_RESTLENGTH 2

class ParticleSpring : public ParticleForceGenerator
{
private:

	// other anchor
	Particle* m_other; 

	// Spring constants
	float m_k; 
	float m_restLength; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	ParticleSpring(Particle*);
	ParticleSpring(Particle*, float m_k, float m_restLength);

	/*-------------- METHODES --------------*/

	void updateForce(Particle* particle, float duration);

};