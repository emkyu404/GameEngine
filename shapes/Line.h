#pragma once
#include <GLEW/glew.h>
#include "Shape.h"
#include <VAO.h>
#include <VBO.h>
#include <IBO.h>
#include "Vector3D.hpp"

class Line : public Shape
{
public:
    Line(VAO* _vao, Vector3D _start, Vector3D _end);
    void init();
    void cleanup();
    void draw();

private:
    Vector3D startPosition, endPosition;
    bool isInited;
    VBO* vbo; VAO* vao; IBO* ibo;
};
