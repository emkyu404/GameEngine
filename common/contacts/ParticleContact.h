#pragma once
#include <Particle.hpp>

class ParticleContact {

public :

	Particle* particle[2];
	float restitution;
	float penetration;
	Vector3D contactNormal;
	Vector3D particleMovement[2];

	void resolve(float _duration);
	float calculateSeparatingVelocity() const;

private :

	void resolveVelocity(float _duration);
	void resolveInterpenetration();
};