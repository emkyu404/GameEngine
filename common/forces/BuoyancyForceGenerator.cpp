#include "BuoyancyForceGenerator.h"
#include "ObjectForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

BuoyancyForceGenerator::BuoyancyForceGenerator()
	: BuoyancyForceGenerator(DEFAULT_MAX_DEPTH, DEFAULT_VOLUME, DEFAULT_WATER_HEIGHT, DEFAULT_LIQUID_DENSITY) 
{
}

BuoyancyForceGenerator::BuoyancyForceGenerator(float _m_maxDepth, float _m_volume)
	: BuoyancyForceGenerator(_m_maxDepth, _m_volume, DEFAULT_WATER_HEIGHT, DEFAULT_LIQUID_DENSITY) {
}

BuoyancyForceGenerator::BuoyancyForceGenerator(float _m_maxDepth, float _m_volume, float _m_waterHeight)
	: BuoyancyForceGenerator(_m_maxDepth, _m_volume, _m_waterHeight, DEFAULT_LIQUID_DENSITY) {
}

BuoyancyForceGenerator::BuoyancyForceGenerator(float _m_maxDepth, float _m_volume, float _m_waterHeight, float _m_liquidDensity) {
	m_maxDepth = _m_maxDepth; 
	m_volume = _m_volume;
	m_waterHeight = _m_waterHeight; 
	m_liquidDensity = _m_liquidDensity; 
}

/*-------------- METHODES --------------*/

void BuoyancyForceGenerator::updateForce(PhysicObject* _particle, float _duration) {
	float depth = _particle->getPosition().getY();

	// Check if we're out of water 
	if (depth >= m_waterHeight + m_maxDepth)
		return; 

	Vector3D F; 

	// Maximum depth 
	if (depth <= m_waterHeight - m_maxDepth)
	{
		F.setY(m_liquidDensity * m_volume); 
	}
	else
	{
		float forceCalculated = m_liquidDensity * m_volume * (depth - m_maxDepth - m_waterHeight) / (2 * m_maxDepth); 
		F.setY(forceCalculated); 
	}

	_particle->addForce(F); 
}