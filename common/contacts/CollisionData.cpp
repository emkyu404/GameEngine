#include "CollisionData.h"

CollisionData::CollisionData(Vector3D _point, Vector3D _normal, float _penetration, float _restitution) {
	point = _point;
	normal = _normal;
	penetration = _penetration;
	restitution = _restitution;
}

Vector3D CollisionData::getPoint()
{
	return point;
}

Vector3D CollisionData::getNormal()
{
	return normal;
}

float CollisionData::getPenetration()
{
	return penetration;
}

float CollisionData::getRestitution()
{
	return restitution;
}
