//
// Created by datin on 3/15/2026.
//

#include <iostream>
#include "VAO.h"
#include "VBO.h"
#include "Application.h"

const int WIDTH = 800;
const int HEIGHT = 800;
const char* TITLE = "OpenGL";


Application::Application() {
    Init();
}

Application::~Application() {
    delete Vbo;
    delete shader;

    glfwTerminate();
}

void Application::Init() {
    if (!glfwInit()) {
        std::cerr<<"ERROR: Failed to initialize glfw";
    }
    window = glfwCreateWindow(WIDTH, HEIGHT, TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(window);

    gladLoadGL(glfwGetProcAddress);

    GLfloat vertices[] = {
         0.5f,  0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
         0.5f, -0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f,     0.0f, 0.0f, 1.0f,
        -0.5f,  0.5f, 0.0f,     0.0f, 1.0f, 0.0f,
         0.0f,  0.9f, 0.0f,     1.0f, 0.0f, 1.0f,
    };

    GLuint indices[] = {
        0, 1, 3,
        1, 2, 3,
        3, 0, 4
    };

    IndexCount = sizeof(indices) / sizeof(GLuint);

    Vao = new VAO();
    Vao->Bind();
    Vbo = new VBO(vertices, sizeof(vertices));
    Vbo->Bind();
    Ebo = new EBO(indices, sizeof(indices));
    Ebo->Bind();

    shader = new Shader("../shaders/vertex.glsl", "../shaders/fragment.glsl");

    Vao->LinkAttrib(*Vbo, 0, 3, GL_FLOAT, 6 * sizeof(float), (void*)0);
    Vao->LinkAttrib(*Vbo, 1, 3, GL_FLOAT, 6 * sizeof(float), (void*)(3*sizeof(float)));

}

void Application::Run() {
    while (!glfwWindowShouldClose(window)) {

        Update();
        Render();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void Application::Update() {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
}

void Application::Render() {
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    shader->use();
    shader->setFloat("time", (float)glfwGetTime());
    glDrawElements(GL_TRIANGLES, IndexCount, GL_UNSIGNED_INT, 0);
}