#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);

// static functions
void processInput(GLFWwindow* win);

int main()
{
    glfwInit();
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
    glClearColor(0.2, 0.5, 0.7, 1.0);
    glViewport(0, 0, 480, 360);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    //Define triangle coordinates
    float coords[] = {
        -0.7, 0.0, 0.0,
         0.7, 0.0, 0.0,
         0.0, 1.0, 0.0
    };
    unsigned int vbId;
    glGenBuffers(1, &vbId);
    glBindBuffer(GL_ARRAY_BUFFER, vbId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);


    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        processInput(window);

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
