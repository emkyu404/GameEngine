#ifndef PARTICLE_H
#define PARTICLE_H

#include "Vector3D.hpp"

#define DEFAULT_VALUE_WEIGHT 1.0f
#define DEFAULT_VALUE_DAMPING 1.0f


class Particle
{
private:
	Vector3D position;
	Vector3D initialPosition; // useful for simulation to place the particle where it is;
	Vector3D velocity;
	Vector3D acceleration;
	float inverseMass;
	float damping;

	Vector3D forceAccumulator;

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

	/*-------------- GETTERS --------------*/
		
	Vector3D getPosition(); 
	Vector3D getInitialPosition();
	Vector3D getVelocity();
	Vector3D getAcceleration();
	float getMass();
	float getInverseMass();
	float getDamping();

	/*-------------- SETTERS --------------*/

	void setPosition(Vector3D); 
	void initializePosition(Vector3D); 
	void setVelocity(Vector3D);
	void setAcceleration(Vector3D);
	void setMass(float);
	void setInverseMass(float); 
	void setDamping(float); 

	void addForce(Vector3D);
	void clearForce();
}; 
#endif