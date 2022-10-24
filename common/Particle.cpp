#include "Particle.hpp"
#include "Vector3D.hpp"
#include <math.h>

/*-------------- CONSTRUCTORS --------------*/

// Default constructor
Particle::Particle()
	: Particle(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT)
{
}

// Default constructor with position
Particle::Particle(Vector3D _position)
	: Particle(_position, Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING)
{
}

// Default constructor with basic vectors 
Particle::Particle(Vector3D _position, Vector3D _velocity, Vector3D _acceleration)
	: Particle(_position, _velocity, _acceleration, DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING)
{
}

// Default constructor with basic vectors and weight 
Particle::Particle(Vector3D _position, Vector3D _velocity, Vector3D _acceleration, float _inverseMass)
	: Particle(_position, _velocity, _acceleration, _inverseMass, DEFAULT_VALUE_DAMPING)
{
}

// Full customization constructor
Particle::Particle(Vector3D _position, Vector3D _velocity, Vector3D _acceleration, float _inverseMass, float _damping) {
	position = _position;
	initialPosition = position;
	velocity = _velocity;
	acceleration = _acceleration;
	inverseMass = _inverseMass;
	damping = _damping; 
	forceAccumulator = Vector3D();
}

/*-------------- METHODES --------------*/

void Particle::integrate(float _deltaTime) {
	acceleration = forceAccumulator * inverseMass;
	velocity = velocity * damping + acceleration * _deltaTime;
	position = position + velocity * _deltaTime;
	clearForce();
}

void Particle::reset()
{
	position = initialPosition;
	velocity = Vector3D();
	acceleration = Vector3D();
	clearForce(); 
}

// Add a force
void Particle::addForce(Vector3D _newForce) {
	forceAccumulator = forceAccumulator + _newForce;
}

// Clear all forces
void Particle::clearForce() {
	forceAccumulator = Vector3D();
}