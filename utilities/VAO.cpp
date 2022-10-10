#include "VAO.h"

VAO::VAO() {
	glGenVertexArrays(1, &id);
}

void VAO::linkVBO(VBO _vbo, GLuint _layout) {
	_vbo.bindVBO();
	glVertexAttribPointer(_layout, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	glEnableVertexAttribArray(_layout);
	_vbo.unbindVBO();
}

void VAO::bindVAO() {
	glBindVertexArray(id);
}

void VAO::unbindVAO() {
	glBindVertexArray(0);
}

void VAO::deleteVAO() {
	glDeleteVertexArrays(1, &id);
}
