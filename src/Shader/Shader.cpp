#include <GL/glew.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include "Shader.h"

#include <glm/glm.hpp>

Shader::Shader(const std::string& VertexShader_filepath, const std::string& FragmentShader_filepath)
{
    std::ifstream VertexShader_stream(VertexShader_filepath);
    std::stringstream VertexShader_source_buffer;
    std::string VertexShader_source;
    VertexShader_source_buffer << VertexShader_stream.rdbuf();
    VertexShader_source = VertexShader_source_buffer.str();

    std::ifstream FragmentShader_stream(FragmentShader_filepath);
    std::stringstream FragmentShader_source_buffer;
    std::string FragmentShader_source;
    FragmentShader_source_buffer << FragmentShader_stream.rdbuf();
    FragmentShader_source = FragmentShader_source_buffer.str();

    id = CreateShader(VertexShader_source, FragmentShader_source);
}
Shader::~Shader()
{
    glDeleteProgram(id);
}

unsigned int Shader::CreateShader(const std::string& VertexShader, const std::string& FragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, VertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, FragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return(program);
}
unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
    unsigned int shader_id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(shader_id, 1, &src, nullptr);
    glCompileShader(shader_id);
    int result;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        std::cout << "Failed to compile shader!" << std::endl;
        glDeleteShader(shader_id);
        return(0);
    }
    return(shader_id);
}

void Shader::Use()
{
    glUseProgram(id);
}
void Shader::StopUse()
{
    glUseProgram(0);
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
    int location = glGetUniformLocation(id, name.c_str());
    if (location == -1) std::cout << "WARNING: uniform " << name << " does not exist";
    return(location); 
}
void Shader::SetUniform1i(const std::string& name, int value)
{
    glUniform1i(GetUniformLocation(name), value);
}
void Shader::SetUniform1iv(const std::string& name, int* values, unsigned int size)
{
    glUniform1iv(GetUniformLocation(name), size, values);
}
void Shader::SetUniform4f(const std::string& name, float value1, float value2, float value3, float value4)
{
    glUniform4f(GetUniformLocation(name), value1, value2, value3, value4);
}
void Shader::SetUniformMatrix4fv(const std::string& name, const glm::mat4& matrix)
{
    glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, &matrix[0][0]);
}