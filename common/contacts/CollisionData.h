#pragma once
#include "Vector3D.hpp";

class CollisionData {

private:
	Vector3D point; // point of contact between object, world coordinate
	Vector3D normal; // normal of contact, world coordinate
	float penetration; //penetration depth
	float restitution; //coefficient of restitution

public:
	CollisionData(Vector3D point, Vector3D normal, float penetration, float restitution);

	Vector3D getPoint();
	Vector3D getNormal();
	float getPenetration();
	float getRestitution();
};