#include <GL/glew.h>

#include "VertexArray.h"

VertexArray::VertexArray()
{
	glGenVertexArrays(1, &vao);
}
VertexArray::~VertexArray()
{
	glDeleteVertexArrays(1, &vao);
}

#include <iostream>
void VertexArray::Bind()
{
	glBindVertexArray(vao);
}

void VertexArray::UnBind()
{
	glBindVertexArray(0);
}