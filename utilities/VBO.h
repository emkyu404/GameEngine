#pragma once

#include <GLEW/glew.h>

// Inspired by https://github.com/VictorGordan/opengl-tutorials
class VBO
{
public:
	GLuint id;

	VBO(GLfloat* _vertices, GLsizeiptr _size);

	void bindVBO();
	void unbindVBO();
	void deleteVBO();
};