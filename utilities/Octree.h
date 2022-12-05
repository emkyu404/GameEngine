#pragma once
#include <vector>
#include "Node.h"
#include "Vector3D.hpp"
#include "RigidBody.h"

class Octree {

private :

	vector<vector<RigidBody*>> listRigibodies; 

public :

	/*-------------- CONSTRUCTORS --------------*/

	Octree();

	/*-------------- GETTERS --------------*/

	vector<vector<RigidBody*>> getRigidbodies(); 

	/*-------------- METHODS --------------*/

	Node* createOctree(Vector3D _center, float _firstHalfWidth, int _maximumDepth, vector<RigidBody*> _allRigidBodies);
	void iterateThroughOctree(Node* _node, int _stopDepth); 
	void insertRb(Node* _pTree, RigidBody* _rigidBody);

	void addNode(Node* _node);
	void removeNode(Node _node);
};

