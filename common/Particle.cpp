#include "Particle.hpp"
#include "Utils.hpp"
#include "../Vector3D.hpp"

Particle::Particle()
{
	Particle(new Vector3D(0, 0, 0), new Vector3D(0, 0, 0), new Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING); 
}

Particle::Particle(Vector3D* _position)
{
	Particle(_position, new Vector3D(0, 0, 0), new Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING);
}

Particle::Particle(Vector3D* _position, Vector3D* _velocity, Vector3D* _acceleration)
{
	Particle(_position, _velocity, _acceleration, DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING);
}

Particle::Particle(Vector3D* _position, Vector3D* _velocity, Vector3D* _acceleration, float _weight)
{
	Particle(_position, _velocity, _acceleration, _weight, DEFAULT_VALUE_DAMPING);
}

Particle::Particle(Vector3D* _position, Vector3D* _velocity, Vector3D* _acceleration, float _weight, float _damping)
{
	position = _position;
	velocity = _velocity;
	acceleration = _acceleration;
	weight = _weight;
	damping = _damping; 
}

void Particle::Integrate(float _deltaTime, Vector3D _sumForces)
{
	// Calculate new positon 
	Vector3D* newPosition = position + velocity * _deltaTime + (acceleration * _deltaTime ^ 2 / 2); 
	position = newPosition; 

	// Update acceleration 
	Utils _utils = *(new Utils()); 
	Vector3D* newAcceleration = GetInverseWeight() * _sumForces + _utils.accelerationGravity; 

	// Update velocity 
	Vector3D* newVelocity = velocity + acceleration * _deltaTime; 
	velocity = newVelocity; 
}

Vector3D* Particle::GetPosition()
{
	return position; 
}

Vector3D* Particle::GetVelocity()
{
	return velocity;
}

Vector3D* Particle::GetAcceleration()
{
	return acceleration;
}

float Particle::GetWeight()
{
	return weight;
}

float Particle::GetInverseWeight()
{
	return 1 / weight; 
}

void Particle::SetPosition(Vector3D* _position)
{
	position = _position; 
}

void Particle::SetSpeed(Vector3D* _velocity)
{
	velocity = _velocity;
}

void Particle::SetAcceleration(Vector3D* _acceleration)
{
	acceleration = _acceleration;
}

void Particle::SetWeight(float _weight)
{
	weight = _weight; 
}

void Particle::SetInverseWeight()
{
	weight = 1/weight; 
}