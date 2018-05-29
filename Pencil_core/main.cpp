#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "src\graphics\textures\texture.h"
#include "src\graphics\shaders\shader.h"
#include "src\utils\Timer.h"
#include "ext\stb_image\stb_image.h"

#include "src\graphics\buffers\vertexarray.h"
#include "src\graphics\buffers\buffer.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp";

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);

// static functions
void processInput(GLFWwindow* win);

void all_inits();

// Global variables
GLenum polygonMode = GL_FILL;
GLFWwindow* window;

#define screenWidth     480.0f
#define screenHeight    360.0f

int main()
{
    using namespace Pencil;
    all_inits();

    Pencil::Shader shader("src/graphics/shaders/basic.vertex", "src/graphics/shaders/basic.fragment");
    shader.disable();

    GLfloat vertices[] = {
        -0.5, -0.5, 0.0,
        -0.5,  0.5, 0.0,
         0.5,  0.5, 0.0,

         -0.5, -0.5, 0.0,
         0.5,  0.5, 0.0,
         0.5, -0.5, 0.0
    };

    VertexArray v;
    v.addBuffer(new Buffer(vertices, 18, 3), 0);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);
       
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
        shader.enable();
        v.bind();
        glDrawArrays(GL_TRIANGLES, 0, 6);
        v.unbind();
        
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

    if(glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
        polygonMode = ((polygonMode==GL_FILL)?GL_LINE:GL_FILL);
}

void all_inits()
{

    char name[32] = { 0 };
    DWORD len = 32L;
    GetComputerName(name, &len);
    name[3] = '\0';

    glfwInit();

    if (strcmp(name, "RAL") != 0) {
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    }

    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(screenWidth, screenHeight, "Pencil game engine", NULL, NULL);
    if (window == NULL) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initilize GLAD" << std::endl;
        exit(-1);
    }
    else {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    glClearColor(1.0, 1.0, 0.8, 1.0);
    glViewport(0, 0, 480, 360);
    glfwSetFramebufferSizeCallback(window, resize_callback);
    glEnable(GL_DEPTH_TEST); 
}