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

/*-------------- GETTERS --------------*/

// Return position 
Vector3D Particle::getPosition() {
	return position; 
}

// Return initial positon 
Vector3D Particle::getInitialPosition() {
	return initialPosition; 
}

// Return velocity 
Vector3D Particle::getVelocity() {
	return velocity;
}

// Return acceleration 
Vector3D Particle::getAcceleration() {
	return acceleration;
}

// Return weight 
float Particle::getMass() {
	return 1.0f / inverseMass;
}

// Return inverse weight 
float Particle::getInverseMass() {
	return inverseMass; 
}

// Return damping
float Particle::getDamping() {
	return damping; 
}

/*-------------- SETTERS --------------*/

// Set Vector3 position 
void Particle::setPosition(Vector3D _position) {
	position = _position; 
}

void Particle::initializePosition(Vector3D _initialPosition) {
	position = _initialPosition; 
	initialPosition = _initialPosition; 
}

// Set Vector3 velocity
void Particle::setVelocity(Vector3D _velocity) {
	velocity = _velocity;
}

// Set Vector3 acceleration
void Particle::setAcceleration(Vector3D _acceleration) {
	acceleration = _acceleration;
}

// Set weight
void Particle::setMass(float _mass) {
	inverseMass = 1.0f / _mass;
}

// Change weight to inverse weight 
void Particle::setInverseMass(float _inverseMass) {
	inverseMass = _inverseMass;
}

// Set damping 
void Particle::setDamping(float _damping) {
	damping = _damping; 
}

// Add a force
void Particle::addForce(Vector3D _newForce) {
	forceAccumulator = forceAccumulator + _newForce;
}

// Clear all forces
void Particle::clearForce() {
	forceAccumulator = Vector3D();
}