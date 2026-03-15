//
// Created by datin on 3/15/2026.
//

#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"
#include <GLFW/glfw3.h>



class Application {
public:
    Application();
    ~Application();

    void Run();
private:
    GLFWwindow* window{};

    VAO* Vao;
    VBO* Vbo;
    EBO* Ebo;

    int IndexCount;

    Shader* shader;

    void Init();
    void Update();
    void Render();
};


#endif //OPENGL_APPLICATION_H