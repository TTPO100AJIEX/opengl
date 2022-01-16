#pragma once

#include <string>

#include <glm/glm.hpp>

class Shader
{
private:
	unsigned int id;
public:
	Shader(const std::string& VertexShader_filepath, const std::string& FragmentShader_filepath);
	~Shader();

	unsigned int CreateShader(const std::string& VertexShader, const std::string& FragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);

	void Use();
	void StopUse();

	unsigned int GetUniformLocation(const std::string& name);

	void SetUniform1i(const std::string& name, int value);
	void SetUniform1iv(const std::string& name, int* values, unsigned int size);
	void SetUniform4f(const std::string& name, float value1, float value2, float value3, float value4);
	void SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix); 
};