#include "Particle.hpp"
#include "Vector3D.hpp"
#include <math.h>

/*-------------- CONSTRUCTORS --------------*/

// Default constructor
Particle::Particle() {
	Particle(Vector3D(0, 0, 0), Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING); 
}

// Default constructor with position
Particle::Particle(Vector3D _position) {
	Particle(_position, Vector3D(0, 0, 0), Vector3D(0, 0, 0),
		DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING);
}

// Default constructor with basic vectors 
Particle::Particle(Vector3D _position, Vector3D _velocity, Vector3D _acceleration) {
	Particle(_position, _velocity, _acceleration, DEFAULT_VALUE_WEIGHT, DEFAULT_VALUE_DAMPING);
}

// Default constructor with basic vectors and weight 
Particle::Particle(Vector3D _position, Vector3D _velocity, Vector3D _acceleration, float _weight) {
	Particle(_position, _velocity, _acceleration, _weight, DEFAULT_VALUE_DAMPING);
}

// Full customization constructor
Particle::Particle(Vector3D _position, Vector3D _velocity, Vector3D _acceleration, float _weight, float _damping) {
	position = _position;
	velocity = _velocity;
	acceleration = _acceleration;
	weight = _weight;
	damping = _damping; 
}

/*-------------- METHODES --------------*/

void Particle::Integrate(float _deltaTime, Vector3D _sumForces) {
	// Calculate new positon 
	Vector3D newPosition = position + velocity * _deltaTime + (( acceleration * pow(_deltaTime, 2)) / 2);
	position = newPosition; 

	// Update acceleration 
	// Vector3D newAcceleration = _sumForces* GetInverseWeight() + .accelerationGravity;

	// Update velocity 
	Vector3D newVelocity = velocity + acceleration * _deltaTime; 
	velocity = newVelocity; 
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
float Particle::GetWeight() {
	return weight;
}

// Return inverse weight 
float Particle::GetInverseWeight() {
	return 1 / weight; 
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
void Particle::SetWeight(float _weight) {
	weight = _weight; 
}

// Change weight to inverse weight 
void Particle::SetInverseWeight() {
	weight = 1/weight; 
}

// Set damping 
void Particle::SetDamping(float _damping) {
	damping = _damping; 
}