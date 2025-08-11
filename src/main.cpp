#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <iostream>

// Vertex Shader source code
const char *vertexShaderSource = "#version 460 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";

// Fragment Shader source code
const char *fragmentShaderSource = "#version 460 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void process_input(GLFWwindow* window);

int main(){
    // Initialize GLFW
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create GLFW window
    GLFWwindow* window = glfwCreateWindow(800, 800, "OpenGL", NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSwapInterval(1); // Enable V-sync

    // Vertex data for first rectangle (touching the left border)
    GLfloat rect1vert[] = {
        -0.5f,  0.5f, 0.0f,  // top right
         0.0f, -0.5f, 0.0f,  // bottom right
        -1.0f, -0.5f, 0.0f,  // bottom left
        -1.0f,  0.5f, 0.0f   // top left
    };

    // Vertex data for second rectangle (touching the right border)
    GLfloat rect2vert[] = {
         1.0f,  0.5f, 0.0f,  // top right
         1.0f, -0.5f, 0.0f,  // bottom right
         0.0f, -0.5f, 0.0f,  // bottom left
         0.5f,  0.5f, 0.0f   // top left
    };

    // Indices to form two triangles per rectangle (0-1-3 and 1-2-3)
    GLuint indices1[] = {
        0, 1, 3,
        1, 2, 3
    };

    GLuint indices2[] = {
        2, 3, 0,
        0, 1, 2
    };
    // Load OpenGL functions using GLAD
    gladLoadGL(glfwGetProcAddress);
    glClearColor(0.2f, 0.5f, 0.1f, 1.0f); // Set background color

    const GLubyte* version = glGetString(GL_VERSION);
    const GLubyte* renderer = glGetString(GL_RENDERER);
    const GLubyte* vendor = glGetString(GL_VENDOR);
    const GLubyte* glslVersion = glGetString(GL_SHADING_LANGUAGE_VERSION);

    printf("OpenGL Version: %s\n", version);
    printf("GLSL Version: %s\n", glslVersion);
    printf("Renderer: %s\n", renderer);
    printf("Vendor: %s\n", vendor);

    // Compile and link shaders
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    glUseProgram(shaderProgram); // Activate the shader program

    // Delete shaders after linking
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    // Vertex Array Objects, Vertex Buffer Objects, and Element Buffer Objects
    GLuint VAOs[2], VBOs[2], EBOs[2];
    glGenVertexArrays(2, VAOs);
    glGenBuffers(2, VBOs);
    glGenBuffers(2, EBOs);

    // --- Rectangle 1 setup ---
    glBindVertexArray(VAOs[0]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[0]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect1vert), rect1vert, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices1), indices1, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Position attribute
    glEnableVertexAttribArray(0);

    // --- Rectangle 2 setup ---
    glBindVertexArray(VAOs[1]);
    glBindBuffer(GL_ARRAY_BUFFER, VBOs[1]);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBOs[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(rect2vert), rect2vert, GL_STATIC_DRAW);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices2), indices2, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0); // Position attribute
    glEnableVertexAttribArray(0);


    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    // --- Main render loop ---
    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT); // Clear the screen

        process_input(window); // Handle keyboard input

        // Draw first rectangle (left)
        glBindVertexArray(VAOs[0]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        // Draw second rectangle (right)
        glBindVertexArray(VAOs[1]);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        glfwSwapBuffers(window); // Swap the front and back buffers
        glfwPollEvents();        // Poll for and process events
    }

    // Clean up resources
    glDeleteVertexArrays(2, VAOs);
    glDeleteBuffers(2, VBOs);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

// Callback function to resize the viewport when the window is resized
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// Process user input
void process_input(GLFWwindow* window) {
    // Pressing ESC will close the window
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GL_TRUE);
    }
}
