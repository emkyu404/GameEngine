#pragma once
#include <GLEW/glew.h>
#include "Shape.h"

class Triangle : public Shape
{
public:
    Triangle();
    ~Triangle();
    void init();
    void cleanup();
    void draw();

private:
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
};
