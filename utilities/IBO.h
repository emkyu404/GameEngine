#pragma once

#include <GLEW/glew.h>

// Inspired by https://github.com/VictorGordan/opengl-tutorials
class IBO
{
public:
	GLuint id;
	IBO(GLuint* _indices, GLsizeiptr _size);

	void bindIBO();
	void unbindIBO();
	void deleteIBO();
};