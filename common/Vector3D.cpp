#include "Vector3D.hpp"

/*-------------- CONSTRUCTORS --------------*/

// Default constructor
Vector3D::Vector3D() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

// Parameter constructor
Vector3D::Vector3D(float _X, float _Y, float _Z) {
	this->x = _X;
	this->y = _Y;
	this->z = _Z;
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
void Vector3D::setVector3D(float _X, float _Y, float _Z) {
	this->x = _X;
	this->y = _Y;
	this->z = _Z;
}

// Set x
void Vector3D::setX(float _X) {
	this->x = _X;
}

// Set y
void Vector3D::setY(float _Y) {
	this->y = _Y;
}

// Set z
void Vector3D::setZ(float _Z) {
	this->z = _Z;
}

/*-------------- OPERATORS --------------*/

// Addition two vectors
Vector3D Vector3D::operator + (Vector3D _vector) {
	return Vector3D(_vector.getX() + this->x, _vector.getY() + this->y, _vector.getZ() + this->z);
}

// Substract two vectors
Vector3D Vector3D::operator - (Vector3D _vector) {
	return Vector3D(this->x - _vector.getX(), this->y - _vector.getY(), this->z - _vector.getZ());
}

// Product by a scalar
Vector3D Vector3D::operator * (float _scalar) {
	return Vector3D(this->x * _scalar, this->y * _scalar, this->z * _scalar);
}

// Divide by a scalar
Vector3D Vector3D::operator / (float _scalar) {
	if (_scalar != 0) {
		return Vector3D(this->x / _scalar, this->y / _scalar, this->z / _scalar);
	}
	return Vector3D();
}

// Equal 
void Vector3D::operator = (Vector3D _vector)
{
	this->x = _vector.getX();
	this->y = _vector.getY();
	this->z = _vector.getZ();
}

// Vectorial product
Vector3D Vector3D::operator ^ (Vector3D _vector) {
	Vector3D newVector = Vector3D();

	newVector.setX((this->y * _vector.getZ()) - (this->z * _vector.getY()));
	newVector.setY((this->z * _vector.getX()) - (this->x * _vector.getZ()));
	newVector.setX((this->x * _vector.getY()) - (this->y * _vector.getX()));

	return newVector;
}

// Scalar product
float Vector3D::operator & (Vector3D _vector) {
	return (this->x * _vector.getX() + this->y * _vector.getY() + this->z * _vector.getZ());
}

Vector3D Vector3D::operator += (Vector3D _vector) {
	return Vector3D(this->x + _vector.getX(), this->y + _vector.getY(), this->z + _vector.getZ());
}

Vector3D Vector3D::operator -= (Vector3D _vector) {
	return Vector3D(this->x - _vector.getX(), this->y - _vector.getY(), this->z - _vector.getZ());
}

/*-------------- METHODES --------------*/

// Invert coordinates of the vector
void Vector3D::invert() {
	this->x = -x;
	this->y = -y;
	this->z = -z;
}

// Compare two vectors
bool Vector3D::isEquals(Vector3D _vector) {
	if (this->x == _vector.getX() && this->y == _vector.getY() && this->z == _vector.getZ()) {
		return true;
	}
	return false;
}

// Norme
float Vector3D::norm() {
	// Norme = sqrt(x² + y² + z²)
	return (float)sqrt(*this & *this);
}

float Vector3D::norm(Vector3D _vector) {
	// Norme entre deux vecteurs = sqrt((x1-x2)² + (y1-y2)² + (z1-z2)²)
	return (float)sqrt((*this - _vector) & (*this - _vector));
}

// Normalize
Vector3D Vector3D::normalize() {
	return (*this / norm());
}

// Clear the Vector
void Vector3D::clear() {
	this->x = 0;
	this->y = 0;
	this->z = 0;
}

Vector3D Vector3D::cross(Vector3D _vector)
{
	return Vector3D(this->y * _vector.z -  this->z * _vector.y, 
					this->z * _vector.x - this->x * _vector.z, 
					this->x * _vector.y - this->y * _vector.x);
}

/*-------------- DISPLAY --------------*/

void Vector3D::print() {
	cout << "x = " << this->x << endl;
	cout << "y = " << this->y << endl;
	cout << "z = " << this->z << endl;
}
