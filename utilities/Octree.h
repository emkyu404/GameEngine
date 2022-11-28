#pragma once
#include <vector>
#include "Node.h"
#include "Vector3D.hpp"
#include "RigidBody.h"

class Octree {

private :

	vector<Node*> listNodes;

public :

	/*-------------- CONSTRUCTORS --------------*/

	Octree();
	Octree(vector<Node*> _listNodes);

	/*-------------- GETTERS --------------*/

	vector<Node*> getNodes();

	/*-------------- METHODS --------------*/

	Node* createOctree(Vector3D _center, float _halfWidth, int _stopDepth);
	void insertRb(Node* _pTree, RigidBody* _rigidBody);

	void addNode(Node* _node);
	void removeNode(Node _node);
};

