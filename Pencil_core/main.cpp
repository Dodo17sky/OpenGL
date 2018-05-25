#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "src\graphics\shaders\shader.h"

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);

// static functions
void processInput(GLFWwindow* win);

int main()
{
    glfwInit();
        // Core OpenGL requires that we use a VAO so it knows what to do with our vertex inputs. 
        // In OpenGL 3.3 is not generated any default vertex array
        // Newer version will auto generate a default vertex array
        // If we fail to bind a VAO, OpenGL will most likely refuse to draw anything.
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(480, 360, "Pencil game engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initilize GLAD" << std::endl;
        return -1;
    }
    std::cout << glGetString(GL_VERSION) << std::endl;
    glClearColor(0.2, 0.5, 0.7, 1.0);
    glViewport(0, 0, 480, 360);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    Pencil::Shader shader("src/graphics/shaders/basic.vertex", "src/graphics/shaders/basic.fragment");

    //Define triangle coordinates
    float coords[] = {
        -0.7, 0.0, 0.0,
         0.7, 0.0, 0.0,
         0.0, 1.0, 0.0
    };
    GLuint vbId, VAO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &vbId);
    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, vbId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0); 

    shader.enable();

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

        // OpenGL version 3.3 - we have a VAO binded before
        glDrawArrays(GL_TRIANGLES, 0, 3); 

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    glfwTerminate();

    return 0;
}

void resize_callback(GLFWwindow* win, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow * win)
{
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, 1);
}
