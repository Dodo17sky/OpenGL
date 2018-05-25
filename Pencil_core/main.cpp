#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "src\graphics\shaders\shader.h"
#include "src\utils\Timer.h"

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);

// static functions
void processInput(GLFWwindow* win);

// Global variables
GLenum polygonMode = GL_FILL;

int main()
{
    using namespace Pencil;

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
    else {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    glClearColor(0.2, 0.5, 0.7, 1.0);
    glViewport(0, 0, 480, 360);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    Pencil::Shader shader("src/graphics/shaders/basic.vertex", "src/graphics/shaders/basic.fragment");
    shader.disable();

    //Define triangle coordinates
    float coords[] = {
        /***      POSITION      /**         COLOR          /**/
        /**/ -0.7, -0.7, 0.0,   /**/    1.0f, 0.0f, 0.0f,  /**/
        /**/ -0.7,  0.7, 0.0,   /**/    0.0f, 1.0f, 0.0f,  /**/
        /**/  0.7,  0.7, 0.0,   /**/    0.0f, 0.0f, 1.0f,  /**/
        /**/  0.7, -0.7, 0.0,   /**/    0.0f, 1.0f, 0.0f   /**/
    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    GLuint VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    
    // Step 1: Bind Vertex-Array
    glBindVertexArray(VAO);
    
    // Step 2: Send array of vertices to gpu - all positions
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);

    // Step 3: Send array of indices to gpu - what positions to use
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // Step 4: set "Vertex attribute"
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    Timer timer;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

        shader.enable();
        glBindVertexArray(VAO);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        timer.printFPS();

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
