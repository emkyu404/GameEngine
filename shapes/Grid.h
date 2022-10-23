#pragma once

#include <GLEW/glew.h>
#include "Shape.h"
#include <VAO.h>
#include <VBO.h>
#include <IBO.h>

const int SLICES = 10;

class Grid : public Shape
{
public:
    Grid(VAO* _vao);
    void init();
    void cleanup();
    void draw();

private:
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
    int slices, length;

    VBO* vbo; VAO* vao; IBO* ibo;
};
