#include <GL/glew.h>

#include "VertexBuffer.h"

#include <iostream>

VertexBuffer::VertexBuffer(const void* data, unsigned int size, unsigned int type)
{
	last_attribute = -1;
	glGenBuffers(1, &id);
	glBindBuffer(GL_ARRAY_BUFFER, id);
	if (type == Type::Static)
	{
		glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	}
	if (type == Type::Dynamic)
	{
		glBufferData(GL_ARRAY_BUFFER, size, nullptr, GL_DYNAMIC_DRAW);
	}
}
void VertexBuffer::AddAttribute(unsigned int amount, unsigned int stride, const void* offset)
{
	last_attribute++;
	glEnableVertexAttribArray(last_attribute);
	glVertexAttribPointer(last_attribute, amount / sizeof(float), GL_FLOAT, GL_FALSE, stride, offset);
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &id);
}

void VertexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void VertexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}