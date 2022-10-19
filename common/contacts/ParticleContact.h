#pragma once
#include <Particle.hpp>

class ParticleContact {

public :

	/* Contains two particles that are involved in the contact 
	The second one can be NULL for contacts with the scenery*/
	Particle* particle[2];
	/* The normal restution coeficient at the contact */
	float restitution;
	float penetration;
	/* Direction of the contact */
	Vector3D contactNormal;
	Vector3D particleMovement[2];

	/* Resolves this contact for both velocity and interpretation */
	void resolve(float _duration);
	/* Calculates the separating velocity at this contact */
	float calculateSeparatingVelocity() const;

private :

	void resolveVelocity(float _duration);
	void resolveInterpenetration();
};