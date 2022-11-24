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
	halfWidth = _parent->getHalfWidth() / 2;
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

Node** Node::getChilds()
{
	return this->childs; 
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

		if (xMin >= x && x <= xMax)
		{
			if (yMin >= y && y <= yMax)
			{
				if (zMin >= z && z <= zMax)
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
	if (!getObjectInIt)
		return; 

	//int iChild = 0; 
	//for (Node* childNode : childs)
	//{
	//	float xChild = center.getX() + halfWidth; 

	//	if (iChild > 4)
	//		xChild = center.getX() - halfWidth;

	//	

	//	childNode = &Node(this, centerChild); 
	//}
}
