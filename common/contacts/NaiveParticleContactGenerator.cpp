#include <NaiveParticleContactGenerator.h>



NaiveParticleContactGenerator::NaiveParticleContactGenerator() 
	: NaiveParticleContactGenerator(DEFAULT_RADIUS, vector<Particle*>()) {

}

NaiveParticleContactGenerator::NaiveParticleContactGenerator(float _radius) 
	: NaiveParticleContactGenerator(_radius, vector<Particle*>()) {
}
/* Full constructor */
NaiveParticleContactGenerator::NaiveParticleContactGenerator(float _radius, vector<Particle*> _particles) {
	radius = _radius;
	particles = _particles;
}

unsigned int NaiveParticleContactGenerator::addContact(ParticleContact* contact, unsigned int limit) const
{
	for (int i = 0; i < particles.size() - 1; ++i) {
		for (int j = i + 1; j < particles.size(); ++j) {
			float distance = particles[i]->getPosition().norm(particles[j]->getPosition());
			if (distance > 2 * radius) {
				return 0;
			}
			contact->particle[0] = particles[i];
			contact->particle[1] = particles[j];
			//normal calculation
			Vector3D normal = particles[j]->getPosition() - particles[i]->getPosition();
			normal.normalize();
			contact->contactNormal = normal;
			//penetration calculation
			contact->penetration = distance - ((distance - radius) * 2);

			contact->restitution = 1;

			return 1;
			
		}
	}

	

	
}