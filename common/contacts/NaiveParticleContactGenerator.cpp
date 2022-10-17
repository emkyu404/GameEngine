#include <NaiveParticleContactGenerator.h>

NaiveParticleContactGenerator::NaiveParticleContactGenerator() 
	: NaiveParticleContactGenerator(DEFAULT_RADIUS) {

}

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float _radius){
	radius = _radius;
}
/* Full constructor */
NaiveParticleContactGenerator::NaiveParticleContactGenerator(float _radius, vector<Particle*> _particles) {
	radius = _radius;
	particles = _particles;
}

unsigned int NaiveParticleContactGenerator::addContact(ParticleContact* _contact, unsigned int _limit) const
{
	unsigned int contactUsed = 0;

	// Iterate through every pairs of particles
	for (int i = 0; i < particles.size() - 1; ++i) {
		for (int j = i + 1; j < particles.size(); ++j) {

			// check if contact used is greater of equal to limit, return the contactUsed
			if (contactUsed >= _limit) {
				return contactUsed;
			}

			// calculate distance between particule
			float distance = particles[i]->getPosition().norm(particles[j]->getPosition());

			// check if distance is less or equal than radius times two
			if (distance <= 2 * radius) {
				_contact->particle[0] = particles[i];
				_contact->particle[1] = particles[j];
				//normal calculation
				Vector3D normal = particles[j]->getPosition() - particles[i]->getPosition();
				normal.normalize();
				_contact->contactNormal = normal;
				//penetration calculation
				_contact->penetration = distance - ((distance - radius) * 2);
				_contact->restitution = 1;

				contactUsed++; // increment number of contact used
				_contact += 1; //we go to another
			}
		}
	}

	return contactUsed;

	

	
}

bool NaiveParticleContactGenerator::particleIsInvolved(Particle* _particle)
{
	return true; // NaiveParticleContactGenerator gets all particules of our world, always return true
}

string NaiveParticleContactGenerator::type()
{
	return "NaiveParticleContactGenerator";
}
