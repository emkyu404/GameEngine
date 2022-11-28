#include "Octree.h"

/*-------------- CONSTRUCTORS --------------*/

Octree::Octree() {
	listNodes = vector<Node*>();
}

Octree::Octree(vector<Node*> _listNodes) {
	listNodes = _listNodes;
}

/*-------------- GETTERS --------------*/

vector<Node*> Octree::getNodes() {
	return listNodes;
}

Node* Octree::createOctree(Vector3D _center, float _halfWidth, int _stopDepth) {
	if (_stopDepth < 0) return NULL;

	else {
		Node* ptrNode = new Node();
		ptrNode->setCenter(_center);
		ptrNode->setHalfWidth(_halfWidth);
		ptrNode->setListStudiedRigidbodies(vector<RigidBody*>(NULL));

		// Recursivly construct child
		Vector3D offset = Vector3D();
		float step = _halfWidth * 0.5f;
		for (int i = 0; i < 8; i++) {

			if (i & 1) {
				offset.setX(step);
			}
			else {
				offset.setX(-step);
			}
			if (i & 2) {
				offset.setY(step);
			}
			else {
				offset.setY(-step);
			}
			if (i & 4) {
				offset.setZ(step);
			}
			else {
				offset.setZ(-step);
			}

			//ptrNode->getChilds().i = createOctree(_center + offset, step, _stopDepth - 1);
		}
		return ptrNode;
	}
	
}