#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

class ParticleGravity : public ParticleForceGenerator
{
private:

	Vector3D m_gravity; 

public:

	void UpdateForce(Particle* particle, float duration); 

};