//
// Created by datin on 3/15/2026.
//

#ifndef OPENGL_APPLICATION_H
#define OPENGL_APPLICATION_H

#include "Shader.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
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
    GLFWwindow *window{};

    VAO *Vao;
    VBO *Vbo;
    EBO *Ebo;

    int IndexCount;

    glm::mat4 trans = glm::mat4(1.0f);

    Shader *shader;

    void Init();

    void Update();

    void Render();
};


#endif //OPENGL_APPLICATION_H
