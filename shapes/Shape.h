#pragma once
#ifndef SHAPE_H
#define SHAPE_H
#include <GLEW/glew.h>

class Shape {
	public:
		virtual void init() = 0;
		virtual void cleanup() = 0;
		virtual void draw() = 0;
};

#endif