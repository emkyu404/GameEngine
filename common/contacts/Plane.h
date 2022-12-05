#pragma once
#include "Primitive.h"
#include "Box.h"

class Plane : public Primitive {
protected:
	Vector3D normal; // normal of plane
	float offset; // off set along the normal of the plane

	public : 
		Plane(RigidBody* _rigidBody, Vector3D normal);
		Plane(RigidBody* _rigidBody, Vector3D normal, float offset);
		float distanceToPlane(Vector3D _point);
		Vector3D closestPointToPlane(Vector3D _point);
		vector<CollisionData> evaluateCollision(Primitive* _other) override;
		vector<CollisionData> evaluateCollision(Box* _other);
};