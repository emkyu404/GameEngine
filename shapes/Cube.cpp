#include "Cube.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


Cube::Cube() : Cube(Vector3D(1,1,1)) {
}

Cube::Cube(Vector3D _scale) {
	isInited = false;
	vao = new VAO();
	scale = _scale;
}

void Cube::init() {
	/*
	const GLfloat vertices[] = {
	-1.0f,-1.0f,-1.0f, // triangle 1 : begin
	-1.0f,-1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f, // triangle 1 : end
	1.0f, 1.0f,-1.0f, // triangle 2 : begin
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f, // triangle 2 : end
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	-1.0f,-1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	-1.0f,-1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f,-1.0f,
	1.0f,-1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f,-1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f,-1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f, 1.0f, 1.0f,
	-1.0f, 1.0f, 1.0f,
	1.0f,-1.0f, 1.0f
	};*/


	float x_scale = abs(scale.getX());
	float y_scale = abs(scale.getY());
	float z_scale = abs(scale.getZ());

	GLfloat vertices[] = {-1.0f* x_scale,  1.0f * y_scale,  1.0f * z_scale,
						  1.0f * x_scale,  1.0f * y_scale,  1.0f * z_scale,
						  1.0f * x_scale, -1.0f * y_scale,  1.0f * z_scale,
						 -1.0f * x_scale, -1.0f * y_scale,  1.0f * z_scale,
						 -1.0f * x_scale, -1.0f * y_scale, -1.0f * z_scale,
						 -1.0f * x_scale,  1.0f * y_scale, -1.0f * z_scale,
						  1.0f * x_scale,  1.0f * y_scale, -1.0f * z_scale,
						  1.0f * x_scale, -1.0f * y_scale, -1.0f * z_scale };

	GLuint indices[] = {0, 1 ,2, 2, 3 ,0,
						 5, 0 ,3, 3, 4 ,5,
						 6, 5 ,4, 4, 7 ,6,
						 1, 6 ,7, 7, 2 ,1,
						 0, 1 ,6, 6, 5 ,0,
						 3, 2 ,7, 7, 4 ,3 };

	ibo = new IBO(indices, sizeof(indices));


	vao->bindVAO();
	vbo = new VBO(vertices, sizeof(vertices));
	vao->linkVBO(*vbo, 0);
	vao->unbindVAO();

	isInited = true;
}

void Cube::cleanup() {
	if (!isInited) {
		return;
	}

	isInited = false;
}

void Cube::draw() {

	if (!isInited) {
		std::cout << "Cube please call init() before draw()" << std::endl;
	}
	vao->bindVAO();
	vbo->bindVBO();
	ibo->bindIBO();
	glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, nullptr);
	vbo->unbindVBO();
	ibo->unbindIBO();
}