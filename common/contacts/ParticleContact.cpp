#include <ParticleContact.h>;

/*----------------PROTECTED----------------*/

void ParticleContact::resolve(float _duration) {

	resolveVelocity(_duration);
	resolveInterpenetration();

}

float ParticleContact::calculateSeparatingVelocity() const {

	Vector3D relativeVelocity = particle[0]->getVelocity();
	if (particle[1]) {
		relativeVelocity -= particle[1]->getVelocity();
	}
	return relativeVelocity & contactNormal; // Vectorial product
}

/*----------------PRIVATE----------------*/

void ParticleContact::resolveVelocity(float _duration) {

	/* Find the velocity in the direction of the contact */
	float separatingVelocity = calculateSeparatingVelocity();
	
	/* Verify if it needs to be resolved */
	if (separatingVelocity > 0) {
		/* The contact is either separating, or stationary, no impule is required */
		return;
	}

	/* Calculate the new separating velocity */
	float newSepVelocity = -separatingVelocity * restitution;

	/* Check velocity buildup due to acceleration only 
	Vector3D accCausedVelocity = particle[0]->getAcceleration();
	if (particle[1]) accCausedVelocity -= particle[1]->getAcceleration();

	float accCausedSepVelocity = accCausedVelocity & contactNormal * _duration;

	if (accCausedSepVelocity < 0) {
		newSepVelocity += restitution * accCausedSepVelocity;

		if (newSepVelocity < 0) newSepVelocity = 0;
	}*/

	float deltaVelocity = newSepVelocity - separatingVelocity;

	/* Apply the change of velocity to each object in proportion to their inverse mass*/
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1])
		totalInverseMass += particle[1]->getInverseMass();

	if (totalInverseMass <= 0) return;

	/* Calculate the impulse to apply (formule from course) */
	float impulse = deltaVelocity / totalInverseMass;

	Vector3D impulsePerIMass = contactNormal * impulse;

	particle[0]->setVelocity(particle[0]->getVelocity() + 
		impulsePerIMass * particle[0]->getInverseMass()
	);

	if (particle[1]) {
		particle[1]->setVelocity(particle[1]->getVelocity() +
			impulsePerIMass * -particle[1]->getInverseMass()
		);
	}
}

void ParticleContact::resolveInterpenetration() {

	/* If we don't have any penetration skip this step */
	if (penetration <= 0) return;

	/* The movement of each object is based on their inverse mass */
	float totalInverseMass = particle[0]->getInverseMass();
	if (particle[1]) totalInverseMass += particle[1]->getInverseMass();

	/* If all particles have infinite mass, then we do nothing */
	if (totalInverseMass <= 0) return;

	/* Find the amount of penetration resolution per unit of invermass */
	Vector3D movePerIMass = contactNormal * (penetration / totalInverseMass);

	/* Calculate the movement amounts */
	particleMovement[0] = movePerIMass * particle[0]->getInverseMass();

	if (particle[1]) {
		particleMovement[1] = movePerIMass * - particle[1]->getInverseMass();
	}
	else {
		particleMovement[1].clear();
	}

	particle[0]->setPosition(particle[0]->getPosition() - particleMovement[0]);

	if (particle[1]) {
		particle[1]->setPosition(
			particle[1]->getPosition() - particleMovement[1]
		);
	}
}
