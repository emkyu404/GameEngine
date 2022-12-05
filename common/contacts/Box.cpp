#include "Box.h"
#include "Plane.h"

Box::Box(RigidBody* _rigidbody, Matrix34 _offset, Vector3D _halfSize) : Primitive(_rigidbody, _offset) {
	halfSize = _halfSize;
	print();
}

array<Vector3D, 8> Box::getCorners() {
	array<Vector3D, 8> corners;
	float x = 0;
	float y = 0;
	float z = 0;

	float halfSizeX = halfSize.getX();
	float halfSizeY = halfSize.getY();
	float halfSizeZ = halfSize.getZ();

	// eight corners in local position
	corners[0] = Vector3D(x + halfSizeX, y + halfSizeY, z + halfSizeZ); // 1 (+ + +)
	corners[1] = Vector3D(x + halfSizeX, y + halfSizeY, z - halfSizeZ); // 2 (+ + -)
	corners[2] = Vector3D(x + halfSizeX, y - halfSizeY, z + halfSizeZ); // 3 (+ - +)
	corners[3] = Vector3D(x + halfSizeX, y - halfSizeY, z - halfSizeZ); // 4 (+ - -)
	corners[4] = Vector3D(x - halfSizeX, y + halfSizeY, z + halfSizeZ); // 5 (- + +)
	corners[5] = Vector3D(x - halfSizeX, y + halfSizeY, z - halfSizeZ); // 6 (- + -)
	corners[6] = Vector3D(x - halfSizeX, y - halfSizeY, z + halfSizeZ); // 7 (- - +)
	corners[7] = Vector3D(x - halfSizeX, y - halfSizeY, z - halfSizeZ); // 8 (- - -)
	
	Matrix34 transformMatrix = rigidbody->getTransformMatrix();
	//apply transformation of all corners in world coordinates
	
	for (int i = 0; i < 8; ++i) {
		corners[i] = transformMatrix.transformAll(corners[i]);
	}
	
	return corners;
}

void Box::print() {
	printf("Box corners : \n");
	for (auto corner : getCorners()) {
		corner.print();
		printf("--- \n");
	}
	printf("End Box corners \n");
}

vector<CollisionData> Box::evaluateCollision(Primitive* _other)
{
	if (dynamic_cast<Plane*>(_other) != nullptr) {
		return dynamic_cast<Plane*>(_other)->evaluateCollision(this); // call plane evaluation with our box
	}
	return vector<CollisionData>();
}
