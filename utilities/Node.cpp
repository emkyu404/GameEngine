#include "Node.h"

/*-------------- CONSTRUCTORS --------------*/

// Default constructor
Node::Node() {
	Node(DEFAULT_HALF_WIDTH); 
}

// Parameter constructor
Node::Node(float _halfWidth) {
	halfWidth = _halfWidth; 
}

// Constructor by parent
Node::Node(Node* _parent, Vector3D _centerChild)
{
	halfWidth = _parent->getHalfWidth() / 2.0f;
	listStudiedRigibodies = _parent->getListConsideredRigidbodies(); 
	center = _centerChild; 
}

/*-------------- GETTERS --------------*/

Vector3D Node::getCenter()
{
	return this->center;
}

float Node::getHalfWidth()
{
	return this->halfWidth; 
}

vector<Node*> Node::getChilds()
{
	return this->listChilds; 
}

bool Node::hasObjectsInIt()
{
	return this->hasObjects; 
}

vector<RigidBody*> Node::getListStudiedRigidbodies()
{
	return this->listStudiedRigibodies; 
}

vector<RigidBody*> Node::getListConsideredRigidbodies()
{
	return this->listStudiedRigibodies; 
}

/*-------------- SETTERS --------------*/

void Node::setCenter(Vector3D _center)
{
	this->center = _center;
}

void Node::setHalfWidth(float _halfWidth)
{
	this->halfWidth = _halfWidth; 
}

void Node::setListStudiedRigidbodies(vector<RigidBody*> _studiedRigidbodies)
{
	this->listStudiedRigibodies = _studiedRigidbodies; 
}

/*-------------- METHODS --------------*/

bool Node::getObjectInIt()
{
	float xMin = center.getX() - halfWidth; 
	float xMax = center.getX() + halfWidth; 
	float yMin = center.getY() - halfWidth; 
	float yMax = center.getY() + halfWidth; 
	float zMin = center.getZ() - halfWidth; 
	float zMax = center.getZ() + halfWidth; 

	for (RigidBody* object : listStudiedRigibodies)
	{
		Vector3D positionObject = object->getPosition(); 
		float x = positionObject.getX(); 
		float y = positionObject.getY(); 
		float z = positionObject.getZ(); 

		if (x >= xMin && x <= xMax)
		{
			if (y >= yMin && y <= yMax)
			{
				if ( z >= zMin && z <= zMax)
				{
					listConsideredRigidBodies.push_back(object); 
				}
			}
		}	
	}

	hasObjects = listConsideredRigidBodies.size() > 0;
	return hasObjects; 
}

void Node::createChilds()
{
	for (int iChild = 0; iChild < 8; ++iChild)
	{
		float xChild = center.getX() + halfWidth; 

		if (iChild > 4)
			xChild = center.getX() - halfWidth;

		float yChild = center.getY() + halfWidth; 

		if (iChild == 2 || iChild == 3 || iChild == 6 || iChild == 7)
			yChild = center.getY() - halfWidth; 

		float zChild = center.getZ() + halfWidth; 

		if (iChild % 2 == 0)
			zChild = center.getZ() - halfWidth; 

		Vector3D centerChild = Vector3D(xChild, yChild, zChild); 
		Node childNode = Node(this, centerChild); 
		listChilds.push_back(&childNode); 
	}
}
