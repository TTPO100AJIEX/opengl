#include <GL/glew.h>

#include "IndexBuffer.h"
#include <iostream>

IndexBuffer::IndexBuffer(const void* data, unsigned int size)
{
	glGenBuffers(1, &id);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
	amount = size / sizeof(unsigned int);
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &id);
}

void IndexBuffer::Bind()
{
	glBindBuffer(GL_ARRAY_BUFFER, id);
}

void IndexBuffer::UnBind()
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

unsigned int IndexBuffer::GetAmount()
{
	return(amount);
}