#pragma once

class IndexBuffer
{
private:
	unsigned int id;
	unsigned int amount;
public:
	IndexBuffer(const void* data, unsigned int size);
	~IndexBuffer();

	void Bind();
	void UnBind();

	unsigned int GetAmount();
};