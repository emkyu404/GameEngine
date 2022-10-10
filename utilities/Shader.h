#pragma once
#ifndef SHADER_H
#define SHADER_H
#include <GLEW/glew.h>

// Inspired by https://www.youtube.com/watch?v=greXpRqCTKs
class Shader
{
public:
    GLuint programID; // ID of shader
    Shader(const char* _vertexFile, const char* _fragmentFile);

    void activate();
    void deactivate();
};

#endif // SHADER_H