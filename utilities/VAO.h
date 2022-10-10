#pragma once

#include <GLEW/glew.h>
#include "VBO.h"

class VAO
{
public:
	GLuint id;
	VAO();

	void linkVBO(VBO _vbo, GLuint _layout);
	void bindVAO();
	void unbindVAO();
	void deleteVAO();
};