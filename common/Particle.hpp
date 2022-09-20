#ifndef PARTICLE_H
#define PARTICLE_H

#include "common/Vector3D.hpp"

#define DEFAULT_VALUE_WEIGHT 1
#define DEFAULT_VALUE_DAMPING 0


class Particle
{
private:
	Vector3D position;
	Vector3D velocity;
	Vector3D acceleration;
	float weight;
	float damping;

public:

	/*-------------- CONSTRUCTORS --------------*/

	Particle();
	Particle(Vector3D position); 
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration);
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float weight);
	Particle(Vector3D position, Vector3D velocity, Vector3D acceleration, float weight, float damping);

	/*-------------- METHODES --------------*/

	void Integrate(float deltaTime, Vector3D _sumForces);

	/*-------------- GETTERS --------------*/
		
	Vector3D GetPosition(); 
	Vector3D GetVelocity(); 
	Vector3D GetAcceleration(); 
	float GetWeight(); 
	float GetInverseWeight(); 
	float GetDamping(); 

	/*-------------- SETTERS --------------*/

	void SetPosition(Vector3D); 
	void SetVelocity(Vector3D);
	void SetAcceleration(Vector3D);
	void SetWeight(float);
	void SetInverseWeight(); 
	void SetDamping(float); 
}; 
#endif