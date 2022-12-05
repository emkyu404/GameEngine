#include "Quad.h"

Quad::Quad() : Quad(Vector3D(1, 1, 1))
{
}

Quad::Quad(Vector3D _scale)
{
	isInited = false;
	vao = new VAO();
	scale = _scale;
}


void Quad::init() {

	float x_scale = abs(scale.getX());
	float y_scale = abs(scale.getY());
	float z_scale = abs(scale.getZ());

	GLfloat vertices[] = {  -1 * x_scale, -1 * y_scale, 0,
							-1 * x_scale,  1 * y_scale, 0,
							 1 * x_scale,  1 * y_scale, 0,
							 1 * x_scale, -1 * y_scale, 0 };

	GLuint indices[] = { 0, 1 ,2, 2 ,3 ,0 };

	ibo = new IBO(indices, sizeof(indices));


	vao->bindVAO();
	vbo = new VBO(vertices, sizeof(vertices));
	vao->linkVBO(*vbo, 0);
	vao->unbindVAO();

	isInited = true;
}

void Quad::cleanup() {
	if (!isInited) {
		return;
	}

	isInited = false;
}

void Quad::draw() {

	if (!isInited) {
		std::cout << "Quad please call init() before draw()" << std::endl;
	}
	vao->bindVAO();
	vbo->bindVBO();
	ibo->bindIBO();
	glDrawElements(GL_TRIANGLES, 2 * 3, GL_UNSIGNED_INT, nullptr);
	vbo->unbindVBO();
	ibo->unbindIBO();
}