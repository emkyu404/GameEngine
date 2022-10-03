#include "Disc.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


Disc::Disc() {
	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
}

Disc::~Disc() {

}

void Disc::init(GLuint vertexPositionID) {
	//TODO
	isInited = true;
}

void Disc::cleanup() {
	if (!isInited) {
		return;
	}

	if (m_vboVertex) {
		glDeleteBuffers(1, &m_vboVertex);
	}
	if (m_vboIndex) {
		glDeleteBuffers(1, &m_vboIndex);
	}
	if (m_vao) {
		glDeleteVertexArrays(1, &m_vao);
	}

	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
}

void Disc::draw() {

	if (!isInited) {
		std::cout << "please call init() before draw()" << std::endl;
	}
	// TODO
}