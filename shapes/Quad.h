#pragma once
#include <GLEW/glew.h>
#include "Shape.h"
#include "VBO.h"
#include "VAO.h"
#include "IBO.h"
#include "Vector3D.hpp"

class Quad : public Shape
{
public:
    Quad();
    Quad(Vector3D scale);
    void init();
    void cleanup();
    void draw();

private:
    bool isInited;
    VBO* vbo; VAO* vao; IBO* ibo;
    Vector3D scale;
};
