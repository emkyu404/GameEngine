#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <GLEW/glew.h>

// Inspired by https://www.youtube.com/watch?v=greXpRqCTKs
class Shader
{
public:
    GLuint programID; // ID of shader
    Shader(const char* vertexFile, const char* fragmentFile);

    void Activate();
    void Deactivate();
};

#endif // SHADER_H