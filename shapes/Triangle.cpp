#include "Triangle.h"

#include <vector>
#include <iostream>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>


Triangle::Triangle() {
	isInited = false;
	m_vao = 0;
	m_vboVertex = 0;
	m_vboIndex = 0;
}

Triangle::~Triangle() {

}

void Triangle::init(GLuint vertexPositionID) {
    //init Triangle
	glGenVertexArrays(1, &vertexPositionID);
	glBindVertexArray(vertexPositionID);

	/* Tableau de vertices qui représentent les sommets de notre triangle */
	static GLfloat g_vertex_buffer_data[] = {
	   -1.0f, -1.0f, 0.0f,
	   1.0f, -1.0f, 0.0f,
	   0.0f,  1.0f, 0.0f,
	};

	// Generate 1 buffer, put the resulting identifier in vertexbuffer
	glGenBuffers(1, &m_vboVertex);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_vertex_buffer_data), g_vertex_buffer_data, GL_STATIC_DRAW);
	// 1rst attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, m_vboVertex);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);

	isInited = true;
}

void Triangle::cleanup() {
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

void Triangle::draw() {
	
    if (!isInited) {
        std::cout << "please call init() before draw()" << std::endl;
    }
	glDrawArrays(GL_TRIANGLES, 0, 3);
} 