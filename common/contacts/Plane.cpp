#include "Plane.h"

Plane::Plane(RigidBody* _rigidBody, Vector3D _normal, float _offset) : Primitive(_rigidBody)
{
    rigidbody = _rigidBody;
    normal = _normal;
    offset = _offset;
}

float Plane::distanceToPlane(Vector3D _point)
{
    return (_point & normal) - offset;
}

// based on C. Ericson. Real time collision detection, Morgan Kaufmann, Chapter 5, page 127
Vector3D Plane::closestPointToPlane(Vector3D _point) {
    float t = distanceToPlane(_point) / normal.norm();
    return _point - (normal * t);
}

vector<CollisionData> Plane::evaluateCollision(Primitive* _other)
{
    if (dynamic_cast<Box*>(_other) != nullptr) {
        return evaluateCollision(dynamic_cast<Box*>(_other));
    }
    return vector<CollisionData>();
}

vector<CollisionData> Plane::evaluateCollision(Box* box) {
    // Etape 1 : compute each point of the box
    bool flag = false;
    vector<CollisionData> collisionsData = vector<CollisionData>();

    array<Vector3D, 8> boxCorners = box->getCorners(); // array of 8 corners in world coordinates

    for (auto val : boxCorners) {
        if (distanceToPlane(val) < 0) {
            // compute point of contact on plane
            Vector3D pointOfContact = closestPointToPlane(val);

            //evaluate normal of contact
            Vector3D normalOfContact = val - pointOfContact;
            normalOfContact.normalize();

            //evaluate depth of interpenetration
            float interpenetration = abs(distanceToPlane(val));

            //evaluate restitution
            float restitution = 0;

            CollisionData cd = CollisionData(pointOfContact, normalOfContact, interpenetration, restitution);
            collisionsData.push_back(cd);
        }
    }
    return collisionsData;
}
