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

	void Integrate(float deltaTime);
	void Reset();

	/*-------------- GETTERS --------------*/
		
	Vector3D GetPosition(); 
	Vector3D GetInitialPosition(); 
	Vector3D GetVelocity(); 
	Vector3D GetAcceleration(); 
	float GetMass(); 
	float GetInverseMass(); 
	float GetDamping(); 

	/*-------------- SETTERS --------------*/

	void SetPosition(Vector3D); 
	void InitializePosition(Vector3D); 
	void SetVelocity(Vector3D);
	void SetAcceleration(Vector3D);
	void SetMass(float);
	void SetInverseMass(float); 
	void SetDamping(float); 

	void AddForce(Vector3D);
	void ClearForce();
}; 
#endif