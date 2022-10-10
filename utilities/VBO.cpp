#include "VBO.h"

VBO::VBO(GLfloat* _vertices, GLsizeiptr _size) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	glBufferData(GL_ARRAY_BUFFER, _size, _vertices, GL_STATIC_DRAW);
}

void VBO::bindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VBO::unbindVBO() {
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VBO::deleteVBO() {
	glDeleteBuffers(1, &id);
}
