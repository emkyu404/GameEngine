#include <Particle.hpp>

class ParticleContact {

public :

	Particle* particle[2];
	float restitution;
	float penetration;
	Vector3D contactNormal;

protected :

	void resolve(float duration);
	float calculateSeparatingVelocity() const;

private :

	void resolveVelocity();
	void resolveInterpenetration();
};