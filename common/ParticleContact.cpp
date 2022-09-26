#include <ParticleContact.h>;

/*----------------PROTECTED----------------*/

void ParticleContact::resolve(float duration) {

	resolveVelocity();
	resolveInterpenetration();

}

float ParticleContact::calculateSeparatingVelocity() const {
	Vector3D relativeVelocity = particle[0]->GetVelocity();
	if (particle[1]) {
		relativeVelocity -= particle[1]->GetVelocity();
	}
	return relativeVelocity & contactNormal; //vérifier opérateur
}

/*----------------PRIVATE----------------*/

void ParticleContact::resolveVelocity() {
	float separatingVelocity = calculateSeparatingVelocity();
	
	if (separatingVelocity > 0) {
		return;
	}

	float newSepVelocity = -separatingVelocity * restitution;//vérifier opérateur
	float deltaVelocity = newSepVelocity - separatingVelocity;

	float totalInverseMass = particle[0]->GetInverseMass();
	if (particle[1])
		totalInverseMass += particle[1]->GetInverseMass();

	if (totalInverseMass <= 0) return;

	float impulse = deltaVelocity / totalInverseMass;

	Vector3D impulsePerMass = contactNormal * impulse;

	particle[0]->SetVelocity(particle[0]->GetVelocity() + 
		impulsePerMass * particle[0]->GetInverseMass()
	);

	if (particle[1]) {
		particle[1]->SetVelocity(particle[1]->GetVelocity() +
			impulsePerMass * particle[1]->GetInverseMass()
		);
	}
}

void ParticleContact::resolveInterpenetration() {

}
