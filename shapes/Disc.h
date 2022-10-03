#pragma once
#ifndef DISC_H
#define DISC_H

#include <GLEW/glew.h>
#include "Shape.h"

class Disc : public Shape
{
public:
    Disc();
    ~Disc();
    void init(GLuint vertexPositionID);
    void cleanup();
    void draw();

private:
    float xPos, yPos, radius;
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
};

#endif // DISC_H#pragma once
