#include "IBO.h"


IBO::IBO(GLuint* _indices, GLsizeiptr _size) {
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _size, _indices, GL_STATIC_DRAW);
}

void IBO::bindIBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
}

void IBO::unbindIBO() {
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

void IBO::deleteIBO() {
	glDeleteBuffers(1, &id);
}