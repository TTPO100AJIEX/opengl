#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <random>
#include <chrono>

#include "VertexArray/VertexArray.h"
#include "VertexBuffer/VertexBuffer.h"
#include "IndexBuffer/IndexBuffer.h"
#include "Shader/Shader.h"
#include "Window/Window.h"
#include "Texture/Texture.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

int main(void)
{
    std::mt19937_64 rng;
    uint64_t timeSeed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
    std::seed_seq ss { uint32_t(timeSeed & 0xffffffff), uint32_t(timeSeed >> 32) };
    rng.seed(ss);
    std::uniform_real_distribution <float> unif(0, 1);
    std::uniform_real_distribution <float> unif2(0.5f, 1);

    if (!glfwInit()) return -1;
    Window window = Window();
    window.setHints();
    window.Create(750, 750, "Hello World");
    if (!window.Check()) return -1;
    window.Use();

    if (glewInit() != GLEW_OK)
    {
        std::cout << "GLEW Error!" << std::endl;
        glfwTerminate();
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;


    VertexArray vao = VertexArray();
    vao.Bind();


    struct Vertex
    {
        float position[2];
        float texCoords[2];
        float texId;
        float color[4];
    };
    struct Triangle
    {
        int v1;
        int v2;
        int v3;
    };

    /*Vertex vertexes[] = {
        { {100.0f, 100.0f}, {0.0f, 0.0f}, 0.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
        { {300.0f, 100.0f}, {1.0f, 0.0f}, 0.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
        { {300.0f, 300.0f}, {1.0f, 1.0f}, 0.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
        { {100.0f, 300.0f}, {0.0f, 1.0f}, 0.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },

        { {250.0f, 250.0f}, {0.0f, 0.0f}, 1.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
        { {700.0f, 250.0f}, {1.0f, 0.0f}, 1.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
        { {700.0f, 700.0f}, {1.0f, 1.0f}, 1.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
        { {250.0f, 700.0f}, {0.0f, 1.0f}, 1.0f, {unif(rng), unif(rng), unif(rng), unif2(rng)} }
    };
    VertexBuffer vb(vertexes, sizeof(vertexes), VertexBuffer::Static);*/

    VertexBuffer vb(nullptr, 8 * sizeof(Vertex), VertexBuffer::Dynamic);
    vb.AddAttribute(sizeof(Vertex::position), sizeof(Vertex), (const void*)(offsetof(Vertex, position)));
    vb.AddAttribute(sizeof(Vertex::texCoords), sizeof(Vertex), (const void*)(offsetof(Vertex, texCoords)));
    vb.AddAttribute(sizeof(Vertex::texId), sizeof(Vertex), (const void*)(offsetof(Vertex, texId)));
    vb.AddAttribute(sizeof(Vertex::color), sizeof(Vertex), (const void*)(offsetof(Vertex, color)));

    Triangle triangles[] = {
        {0, 1, 2}, {2, 3, 0},
        {4, 5, 6}, {6, 7, 4},
    };
    IndexBuffer ib(triangles, sizeof(triangles));


    Texture texture1("res/textures/avatar.png");
    Texture texture2("res/textures/avatar2.png");
    texture1.Bind(0);
    texture2.Bind(1);


    Shader shader("res/shaders/logo/VertexShader.shader", "res/shaders/logo/FragmentShader.shader");
    shader.Use();
    int samplers[2] = { 0, 1 };
    shader.SetUniform1iv("u_Textures", samplers, sizeof(samplers) / sizeof(int));

    glm::mat4 proj = glm::ortho(0.0f, 750.0f, 0.0f, 750.0f, -1.0f, 1.0f);
    glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0, 0, 0));
    shader.SetUniformMatrix4fv("u_MVP", proj * view * model);


    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    int cou = 0;
    while (!glfwWindowShouldClose(window.getWindow()))
    {
        window.Clear();

        cou++;
        if (cou == 60)
        {
            float tex1 = (unif(rng) > 0.5) ? 1.0f : 0.0f;
            float tex2 = (tex1 == 1.0f) ? 0.0f : 1.0f;
            Vertex vertexes[] = {
                { {100.0f, 100.0f}, {0.0f, 0.0f}, tex1, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
                { {300.0f, 100.0f}, {1.0f, 0.0f}, tex1, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
                { {300.0f, 300.0f}, {1.0f, 1.0f}, tex1, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
                { {100.0f, 300.0f}, {0.0f, 1.0f}, tex1, {unif(rng), unif(rng), unif(rng), unif2(rng)} },

                { {250.0f, 250.0f}, {0.0f, 0.0f}, tex2, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
                { {700.0f, 250.0f}, {1.0f, 0.0f}, tex2, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
                { {700.0f, 700.0f}, {1.0f, 1.0f}, tex2, {unif(rng), unif(rng), unif(rng), unif2(rng)} },
                { {250.0f, 700.0f}, {0.0f, 1.0f}, tex2, {unif(rng), unif(rng), unif(rng), unif2(rng)} }
            };
            vb.Bind();
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertexes), vertexes);
            cou = 0;
        }


        window.Draw(vao, ib, shader);


        glfwSwapBuffers(window.getWindow());
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}