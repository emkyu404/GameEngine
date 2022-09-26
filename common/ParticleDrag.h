#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

class ParticleDrag : public ParticleForceGenerator
{
private:

	float m_k1; 
	float m_k2; 

public:

	void UpdateForce(Particle* particle, float duration);

};