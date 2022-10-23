
#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Line.h"


Line::Line(VAO* _vao, Vector3D _start, Vector3D _end) {
	isInited = false;
	vao = _vao;
	startPosition = _start;
	endPosition = _end;
}

void Line::init() {

	/* Tableau de vertices qui représentent les sommets de notre triangle */
	const GLfloat vertices[] = {
		startPosition.getX(), startPosition.getY(), startPosition.getZ(),
		endPosition.getX(), endPosition.getY(), endPosition.getZ()
	};

	vao->bindVAO();
	vbo = new VBO(vertices, sizeof(vertices));
	vao->linkVBO(*vbo, 0);
	vao->unbindVAO();

	isInited = true;
}

void Line::cleanup(){
}


void Line::draw() {

	if (!isInited) {
		std::cout << "Line please call init() before draw()" << std::endl;
	}
	vao->bindVAO();
	vbo->bindVBO();
	glDrawArrays(GL_LINES, 0, 2);
}