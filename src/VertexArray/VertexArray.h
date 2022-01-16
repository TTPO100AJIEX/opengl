#pragma once

class VertexArray
{
private:
	unsigned int vao;
public:
	VertexArray();
	~VertexArray();

	void Bind();
	void UnBind();
};