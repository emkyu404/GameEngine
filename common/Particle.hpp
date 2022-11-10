#ifndef PARTICLE_H
#define PARTICLE_H

#include "PhysicObject.h"
#include "Vector3D.hpp"

#define DEFAULT_VALUE_WEIGHT 1.0f
#define DEFAULT_VALUE_DAMPING 1.0f


class Particle : public PhysicObject {

public:

	/*-------------- CONSTRUCTORS --------------*/

	Particle();
	Particle(Vector3D position); 
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration);
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass);
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float mass, float damping);

	/*-------------- METHODES --------------*/

	void integrate(float deltaTime);
	void reset();
	void addForce(Vector3D);
	void clearAccumulator();
private:
	void clearForce();

}; 
#endif