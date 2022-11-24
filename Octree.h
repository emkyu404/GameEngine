#pragma once
#include <vector>
#include "Node.h"

class Octree
{
private :

	vector<Node> listNodes;

public :

	/*-------------- CONSTRUCTORS --------------*/

	Octree();
	Octree(vector<Node> _listNodes);

	/*-------------- GETTERS --------------*/

	vector<Node> getNodes();

	/*-------------- METHODS --------------*/

	Node* createOctree(Vector3D center, float halfWidth, int stopDepth);
};

