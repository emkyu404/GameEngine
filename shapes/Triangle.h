#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <GLEW/glew.h>
#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle();
    ~Triangle();
    void init(GLuint vertexPositionID);
    void cleanup();
    void draw();

private:
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
};

#endif // TRIANGLE_H