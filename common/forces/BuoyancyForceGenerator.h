#pragma once
#include "ObjectForceGenerator.h"
#include "Vector3D.hpp"

#define DEFAULT_MAX_DEPTH 5
#define DEFAULT_VOLUME 20
#define DEFAULT_WATER_HEIGHT 4
#define DEFAULT_LIQUID_DENSITY 1

class BuoyancyForceGenerator : public ObjectForceGenerator
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

	BuoyancyForceGenerator();
	BuoyancyForceGenerator(float maxDepth, float volume);
	BuoyancyForceGenerator(float maxDepth, float volume, float waterHeight);
	BuoyancyForceGenerator(float maxDepth, float volume, float waterHeight, float liquidDensity);

	/*-------------- METHODES --------------*/

	void updateForce(PhysicObject* particle, float duration);

};