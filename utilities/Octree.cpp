#include "Octree.h"

/*-------------- CONSTRUCTORS --------------*/

Octree::Octree() {
	listRigibodies = vector<vector<RigidBody*>>();
}

/*-------------- GETTERS --------------*/

vector<vector<RigidBody*>> Octree::getRigidbodies() {
	return listRigibodies;
}

/*-------------- METHODS --------------*/

Node* Octree::createOctree(Vector3D _center, float _firstHalfWidth, int _maximumDepth, vector<RigidBody*> _allRigidBodies) {
	Node* ptrNode = new Node();
	ptrNode->setCenter(_center);
	ptrNode->setHalfWidth(_firstHalfWidth);
	ptrNode->setListStudiedRigidbodies(_allRigidBodies);

	iterateThroughOctree(ptrNode, _maximumDepth); 
}

void Octree::iterateThroughOctree(Node* node, int stopDepth)
{
	if (node->getObjectInIt())
	{
		vector<RigidBody*> consideredRigidbodies = node->getListConsideredRigidbodies(); 
		int sizeListRigidbodies = consideredRigidbodies.size() > 2; 

		// End parcours
		if (stopDepth)
		{
			listRigibodies.push_back(consideredRigidbodies); 
		}

		if (sizeListRigidbodies > 2)
		{
			node->createChilds(); 
			vector<Node*> childs = node->getChilds(); 

			for (int iChild = 0; iChild < 8; ++iChild)
			{
				iterateThroughOctree(childs[iChild], stopDepth - 1); 
			}
		}
		else if (sizeListRigidbodies == 2)
		{
			listRigibodies.push_back(consideredRigidbodies); 
		}
		else
		{
			// No object in node or only one object (useless collision detection)
		}
	}
}