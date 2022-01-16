#include <GLFW/glfw3.h>

#include "Window.h"

void Window::setHints()
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
}

void Window::Create(int width, int height, const std::string& name)
{
    window = glfwCreateWindow(width, height, name.c_str(), NULL, NULL);
}

bool Window::Check()
{
    if (!window)
    {
        glfwTerminate();
        return(false);
    }
    return(true);
}

void Window::Use()
{
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
}

void Window::Clear()
{
    //glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

#include "../VertexArray/VertexArray.h"
#include "../IndexBuffer/IndexBuffer.h"
#include "../Shader/Shader.h"
void Window::Draw(VertexArray& vao, IndexBuffer& ib, Shader& shader)
{
    vao.Bind();
    ib.Bind();
    shader.Use();
    glDrawElements(GL_TRIANGLES, ib.GetAmount(), GL_UNSIGNED_INT, nullptr);
}

GLFWwindow* Window::getWindow()
{
    return(window);
}