#pragma once
#ifndef CUBE_H
#define CUBE_H

#include <GLEW/glew.h>
#include "Shape.h"

class Cube : public Shape
{
public:
    Cube();
    ~Cube();
    void init();
    void cleanup();
    void draw();

private:
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
};

#endif // CUBE_H