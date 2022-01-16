#pragma once

#include <GLFW/glfw3.h>
#include "../VertexArray/VertexArray.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../Shader/Shader.h"

#include <string>

class Window
{
private:
	GLFWwindow* window;
public:
	void setHints();

	void Create(int width, int height, const std::string& name);
	bool Check();
	void Use();

	void Clear();
	void Draw(VertexArray& vao, IndexBuffer& ib, Shader& shader);

	GLFWwindow* getWindow();
};