#include "ParticleGravity.h"
#include "ParticleForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

ParticleGravity::ParticleGravity() : ParticleGravity(EARTH_GRAVITY)
{
}

ParticleGravity::ParticleGravity(Vector3D _gravity)
{
	m_gravity = _gravity; 
}

/*-------------- METHODES --------------*/

void ParticleGravity::UpdateForce(Particle* _particle, float _duration)
{
	Vector3D F = m_gravity * _particle->GetMass();
	_particle->AddForce(F);
}
