#pragma once
#ifndef GRID_H
#define GRID_H

#include <GLEW/glew.h>
#include "Shape.h"

const int SLICES = 10;

class Grid : public Shape
{
public:
    Grid();
    ~Grid();
    void init();
    void cleanup();
    void draw();

private:
    bool isInited;
    GLuint m_vao, m_vboVertex, m_vboIndex;
    int slices, length;
};

#endif // CUBE_H