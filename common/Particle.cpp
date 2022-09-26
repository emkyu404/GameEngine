#include "Particle.hpp"
#include "Vector3D.hpp"
#include <math.h>

/*-------------- CONSTRUCTORS --------------*/

// Default constructor
Particle::Particle()
	: Particle(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING)
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
	velocity = _velocity;
	acceleration = _acceleration;
	inverseMass = _inverseMass;
	damping = _damping; 
	forceAccumulator = Vector3D();
}

/*-------------- METHODES --------------*/

void Particle::Integrate(float _deltaTime) {
	acceleration = forceAccumulator * inverseMass;
	velocity = velocity * damping + acceleration * _deltaTime;
	position = position + velocity * _deltaTime;
	ClearForce();
}

/*-------------- GETTERS --------------*/

// Return position 
Vector3D Particle::GetPosition() {
	return position; 
}

// Return velocity 
Vector3D Particle::GetVelocity() {
	return velocity;
}

// Return acceleration 
Vector3D Particle::GetAcceleration() {
	return acceleration;
}

// Return weight 
float Particle::GetMass() {
	return 1.0f / inverseMass;
}

// Return inverse weight 
float Particle::GetInverseMass() {
	return inverseMass; 
}

// Return damping
float Particle::GetDamping() {
	return damping; 
}

/*-------------- SETTERS --------------*/

// Set Vector3 position 
void Particle::SetPosition(Vector3D _position) {
	position = _position; 
}

// Set Vector3 velocity
void Particle::SetVelocity(Vector3D _velocity) {
	velocity = _velocity;
}

// Set Vector3 acceleration
void Particle::SetAcceleration(Vector3D _acceleration) {
	acceleration = _acceleration;
}

// Set weight
void Particle::SetMass(float _mass) {
	inverseMass = 1.0f / _mass;
}

// Change weight to inverse weight 
void Particle::SetInverseMass(float _inverseMass) {
	inverseMass = _inverseMass;
}

// Set damping 
void Particle::SetDamping(float _damping) {
	damping = _damping; 
}

//
void Particle::AddForce(Vector3D _newForce) {
	forceAccumulator = forceAccumulator + _newForce;
}

void Particle::ClearForce() {
	forceAccumulator = Vector3D();
}