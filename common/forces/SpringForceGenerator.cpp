#include "SpringForceGenerator.h"
#include "ObjectForceGenerator.h"

/*-------------- CONSTRUCTORS --------------*/

SpringForceGenerator::SpringForceGenerator() : SpringForceGenerator(DEFAULT_VALUE_K, DEFAULT_VALUE_RESTLENGTH) {
}

SpringForceGenerator::SpringForceGenerator(float _m_k, float _m_restLength) {
	m_k = _m_k;
	m_restLength = _m_restLength;
}

/*-------------- METHODES --------------*/
