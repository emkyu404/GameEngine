#include "Vector3D.hpp"

/*-------------- CONSTRUCTORS --------------*/

// Default constructor
Vector3D::Vector3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

// Parameter constructor
Vector3D::Vector3D(float X, float Y, float Z) {
	this->x = X;
	this->y = Y;
	this->z = Z;
}

/*-------------- GETTERS --------------*/

// Return himself
Vector3D* Vector3D::getVector3D() {
	return this;
}

// Return x
float Vector3D::getX() {
	return this->x;
}

// Return y
float Vector3D::getY() {
	return this->y;
}

// Return z
float Vector3D::getZ() {
	return this->z;
}

/*-------------- SETTERS --------------*/

// Set himself
void Vector3D::setVector3D(float X, float Y, float Z) {
	this->x = X;
	this->y = Y;
	this->z = Z;
}

// Set x
void Vector3D::setX(float X) {
	this->x = X;
}

// Set y
void Vector3D::setY(float Y) {
	this->y = Y;
}

// Set z
void Vector3D::setZ(float Z) {
	this->z = Z;
}

/*-------------- OPERATORS --------------*/

// Addition two vectors
Vector3D Vector3D::operator + (Vector3D vector) {
	return Vector3D(vector.getX() + this->x, vector.getY() + this->y, vector.getZ() + this->z);
}

// Substract two vectors
Vector3D Vector3D::operator - (Vector3D vector) {
	return Vector3D(this->x - vector.getX(), this->y - vector.getY(), this->z - vector.getZ());
}

// Product by a scalar
Vector3D Vector3D::operator * (float scalar) {
	return Vector3D(this->x * scalar, this->y * scalar, this->z * scalar);
}

// Divide by a scalar
Vector3D Vector3D::operator / (float scalar) {
	if (scalar != 0) {
		return Vector3D(this->x / scalar, this->y / scalar, this->z / scalar);
	}
	return Vector3D();
}

// Equal 
void Vector3D::operator = (Vector3D vector)
{
	this->x = vector.getX();
	this->y = vector.getY();
	this->z = vector.getZ();
}

// Vectorial product
Vector3D Vector3D::operator ^ (Vector3D vector) {
	Vector3D newVector = Vector3D();

	newVector.setX((this->y * vector.getZ()) - (this->z * vector.getY()));
	newVector.setY((this->z * vector.getX()) - (this->x * vector.getZ()));
	newVector.setX((this->x * vector.getY()) - (this->y * vector.getX()));

	return newVector;
}

// Scalar product
float Vector3D::operator & (Vector3D vector) {
	return (this->x * vector.getX() + this->y * vector.getY() + this->z * vector.getZ());
}

/*-------------- METHODES --------------*/

// Invert coordinates of the vector
void Vector3D::invert() {
	this->x = -x;
	this->y = -y;
	this->z = -z;
}

// Compare two vectors
bool Vector3D::isEquals(Vector3D vector) {
	if (this->x == vector.getX() && this->y == vector.getY() && this->z == vector.getZ()) {
		return true;
	}
	return false;
}

// Norme
float Vector3D::norm() {
	// Norme = sqrt(x² + y² + z²)
	return (float)sqrt(*this & *this);
}

// Normalize
Vector3D Vector3D::normalize() {
	return (*this / norm());
}

/*-------------- AFFICHAGE --------------*/

void Vector3D::print() {
	cout << "x = " << this->x << endl;
	cout << "y = " << this->y << endl;
	cout << "z = " << this->z << endl;
}
