#include "Quaternion.h"

/*-------------- CONSTRUCTORS --------------*/

Quaternion::Quaternion()
{
	this->values[0] = 0;
	this->values[1] = 0;
	this->values[2] = 0;
	this->values[3] = 0;
}

// Parameter constructor
Quaternion::Quaternion(float _W, float _I, float _J, float _K) {
	this->values[0] = _W;
	this->values[1] = _I;
	this->values[2] = _J;
	this->values[3] = _K;
}

/*-------------- GETTERS --------------*/

// Return himself
Quaternion* Quaternion::getQuaternion() {
	return this; 
}

// Return w
float Quaternion::getW() {
	return this->values[0];
}

// Return i
float Quaternion::getI() {
	return this->values[1]; 
}

// Return j
float Quaternion::getJ() {
	return this->values[2];
}

// Return k
float Quaternion::getK() {
	return this->values[3];
}

/*-------------- SETTERS --------------*/

// Set W
void Quaternion::setQuaternion(float _W, float _I, float _J, float _K) {
	this->values[0] = _W;
	this->values[1] = _I;
	this->values[2] = _J;
	this->values[3] = _K;
}

// Set W
void Quaternion::setW(float _W) {
	this->values[0] = _W;
}

// Set I
void Quaternion::setI(float _I) {
	this->values[1] = _I;
}

// Set J
void Quaternion::setJ(float _J) {
	this->values[2] = _J;
}

// Set K
void Quaternion::setK(float _K) {
	this->values[3] = _K;
}

/*-------------- OPERATORS --------------*/

// Product by a quaternion
Quaternion Quaternion::operator*(const Quaternion& other)
{
	Quaternion result = Quaternion(); 
	result.values[0] = (this->values[0] * other.values[0] - this->values[1] * other.values[1] - this->values[2] * other.values[2] - this->values[3] * other.values[3]); 
	result.values[1] = (this->values[0] * other.values[1] + this->values[1] * other.values[0] + this->values[2] * other.values[3] - this->values[3] * other.values[2]);
	result.values[2] = (this->values[0] * other.values[2] + this->values[2] * other.values[0] + this->values[3] * other.values[1] - this->values[1] * other.values[3]);
	result.values[3] = (this->values[0] * other.values[3] + this->values[3] * other.values[0] + this->values[1] * other.values[2] - this->values[2] * other.values[1]);
	this->setQuaternion(result.values[0], result.values[1], result.values[2], result.values[3]); 

	return *this; 
}

// Addition by a quaternion
Quaternion Quaternion::operator+(const Quaternion& other)
{
	Quaternion result = Quaternion();
	result.values[0] = (this->values[0] + other.values[0]); 
	result.values[1] = (this->values[1] + other.values[1]);
	result.values[2] = (this->values[2] + other.values[2]);
	result.values[3] = (this->values[3] + other.values[3]);
	this->setQuaternion(result.values[0], result.values[1], result.values[2], result.values[3]);

	return *this;
}

// Product by a scalar 
Quaternion Quaternion::operator*(const float scalar)
{
	Quaternion result = Quaternion(); 
	result.setI(this->getI() * scalar);
	result.setJ(this->getJ() * scalar);
	result.setK(this->getK() * scalar);
	result.setW(this->getW() * scalar);

	return result; 
}

/*-------------- METHODS --------------*/

float Quaternion::getNorm()
{
	return sqrt(this->getW() * this->getW() + this->getI() * this->getI() + this->getJ() * this->getJ() + this->getK() * this->getK());
}

void Quaternion::normalized()
{
	float norm = getNorm(); 

	if (norm == 0)
		return; 

	*this= *this * (1.0f / norm);
}

void Quaternion::rotateByVector(const Vector3D& _vector)
{
	Quaternion byVector = Quaternion(0, _vector.getX(), _vector.getY(), _vector.getZ());
	*this = *this * byVector; 
}

void Quaternion::updateByAngularVelocity(const Vector3D& rotation, float duration)
{
	Quaternion rotatedQuaternion = Quaternion(this->getW(), this->getI(), this->getJ(), this->getK()); 
	rotatedQuaternion.rotateByVector(rotation); 
	*this = *this + (rotatedQuaternion * (duration / 2.0f));
}

/*-------------- DISPLAY --------------*/

void Quaternion::print() {
	cout << "w = " << this->values[0] << endl;
	cout << "i = " << this->values[1] << endl;
	cout << "j = " << this->values[2] << endl;
	cout << "k = " << this->values[3] << endl;
}