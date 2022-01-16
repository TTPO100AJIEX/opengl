#pragma once

class VertexBuffer
{
private:
	unsigned int id;
	unsigned int last_attribute;
public:
	enum Type { Static, Dynamic };

	VertexBuffer(const void* data, unsigned int size, unsigned int type);
	~VertexBuffer();

	void Bind();
	void UnBind();

	void AddAttribute(unsigned int amount, unsigned int stride, const void* offset);
};