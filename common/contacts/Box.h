#pragma once
#include "Primitive.h"
#include <array>

class Box : public Primitive {
	protected :
	Vector3D halfSize;

	public:
		Box(RigidBody* _rigidbody, Matrix34 _offset, Vector3D _halfSize);
		array<Vector3D, 8> getCorners();
		vector<CollisionData> evaluateCollision(Primitive* _other) override;
		void print();
};