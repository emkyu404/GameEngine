#pragma once
#ifndef SHAPE_H
#define SPHERE_H
#include <GLEW/glew.h>

class Shape {
	public:
		virtual void init(GLuint vertexPositionID) = 0;
		virtual void cleanup() = 0;
		virtual void draw() = 0;
};

#endif