#pragma once
#include "ParticleForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_MAX_DEPTH 1
#define DEFAULT_VOLUME 1
#define DEFAULT_WATER_HEIGHT 1
#define DEFAULT_LIQUID_DENSITY 1000

class ParticleBuoyancy : public ParticleForceGenerator
{
private:

	// Particle properties
	float m_maxDepth; 
	float m_volume; 

	// Effect properties
	float m_waterHeight; 
	float m_liquidDensity; 

public:

	/*-------------- CONSTRUCTORS --------------*/

	ParticleBuoyancy();
	ParticleBuoyancy(float maxDepth, float volume);
	ParticleBuoyancy(float maxDepth, float volume, float waterHeight);
	ParticleBuoyancy(float maxDepth, float volume, float waterHeight, float liquidDensity);

	/*-------------- METHODES --------------*/

	void updateForce(Particle* particle, float duration);

};