#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <GLEW/glew.h>
#include "Shape.h"

class Sphere : public Shape
{
public:
    Sphere();
    ~Sphere();
    void init(GLuint vertexPositionID);
    void cleanup();
    void draw();

private:
    int lats, longs;
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
    int numsToDraw;
};

#endif // SPHERE_H