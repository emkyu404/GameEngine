#pragma once
#include <GLEW/glew.h>
#include "Shape.h"
#include "VBO.h"
#include "VAO.h"

class Cube : public Shape
{
public:
    Cube(VAO* vao);
    void init();
    void cleanup();
    void draw();

private:
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
    VBO* vbo; VAO* vao;
};
