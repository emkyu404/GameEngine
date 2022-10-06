#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_K 1
#define DEFAULT_VALUE_RESTLENGTH 2

class ParticleAnchoredSpring : public ParticleForceGenerator
{
private:

	// other anchor
	Vector3D* m_anchor;

	// Spring constants
	float m_k;
	float m_restLength;

public:

	/*-------------- CONSTRUCTORS --------------*/

	ParticleAnchoredSpring(Vector3D*);
	ParticleAnchoredSpring(Vector3D*, float m_k, float m_restLength);

	/*-------------- METHODES --------------*/

	void UpdateForce(Particle* particle, float duration);

};