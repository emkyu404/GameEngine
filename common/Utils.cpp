#include "Utils.hpp"
#include "../Vector3D.hpp"

Utils::Utils()
{
	accelerationGravity = new Vector3D(0, -DEFAULT_GRAVITATIONAL_ACCELERATION, 0); 
}