#include <NaiveParticleContactGenerator.h>

NaiveParticleContactGenerator::NaiveParticleContactGenerator() 
	: NaiveParticleContactGenerator(DEFAULT_RADIUS) {

}

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float _radius){
	radius = _radius;
}

NaiveParticleContactGenerator::NaiveParticleContactGenerator(vector<Particle*>* _particles) 
	: NaiveParticleContactGenerator(DEFAULT_RADIUS, _particles) {

}

/* Full constructor */
NaiveParticleContactGenerator::NaiveParticleContactGenerator(float _radius, vector<Particle*>* _particles) {
	radius = _radius;
	particles = _particles;
}

unsigned int NaiveParticleContactGenerator::addContact(vector<ParticleContact*>* _contactArray, unsigned int _limit) const
{
	unsigned int contactUsed = 0;

	// Iterate through every pairs of particles
	for (int i = 0; i < particles->size() - 1; ++i) {
		for (int j = i + 1; j < particles->size(); ++j) {

			// check if contact used is greater of equal to limit, return the contactUsed
			if (contactUsed >= _limit) {
				return contactUsed;
			}

			// calculate distance between particule
			float distance = particles->at(i)->getPosition().norm(particles->at(j)->getPosition());

			// check if distance is less or equal than radius times two
			if (distance <= 2 * radius) {
				ParticleContact* newContact = new ParticleContact(); //create new contact

				//process all initialization and arithmetics
				newContact->particle[0] = particles->at(i);
				newContact->particle[1] = particles->at(j);
				//normal calculation
				Vector3D normal = particles->at(j)->getPosition() - particles->at(i)->getPosition();
				normal.normalize();
				newContact->contactNormal = normal;
				//penetration calculation
				newContact->penetration = distance - ((distance - radius) * 2);
				newContact->restitution = 1;

				contactUsed++; // increment number of contact used
				_contactArray->push_back(newContact); // add our new contact to array of contact
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
