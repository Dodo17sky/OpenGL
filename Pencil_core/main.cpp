#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "src\graphics\textures\texture.h"
#include "src\graphics\shaders\shader.h"
#include "src\utils\Timer.h"
#include "ext\stb_image\stb_image.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp";

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);

// static functions
void processInput(GLFWwindow* win);

// Global variables
GLenum polygonMode = GL_FILL;

#define screenWidth     480.0f
#define screenHeight    360.0f

int main()
{
    using namespace Pencil;

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

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Pencil game engine", NULL, NULL);
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
        /***      POSITION      /**         COLOR          /**	texture coords	*/
        /**/ -0.9, -0.9, 0.0,   /**/    1.0f, 0.0f, 0.0f,  /**/		0.0, 0.0,	/**///	bottom left
        /**/ -0.9,  0.9, 0.0,   /**/    0.0f, 1.0f, 0.0f,  /**/ 	0.0, 1.0,	/**///	top left
        /**/  0.9,  0.9, 0.0,   /**/    1.0f, 0.0f, 0.0f,  /**/ 	1.0, 1.0,	/**///	top right	
        /**/  0.9, -0.9, 0.0,   /**/    0.0f, 1.0f, 0.0f,  /**/ 	1.0, 0.0 	/**///	bottom right
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)12);
    glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)24);
	glEnableVertexAttribArray(2);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

	Texture tex("timber.jpg");
	tex.unbind();

    glm::mat4 model, view, projection;
    model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), screenWidth/screenHeight, 0.1f, 100.0f);

	shader.enable();
	shader.setUniform1i("ourTexture1", tex.getTextureSlot());


    Timer timer;
	timer.startCount();
	int i = 0;
    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

		tex.bind();

        shader.enable();
        shader.setUniformMatrix4f("model", glm::value_ptr(model));
        shader.setUniformMatrix4f("view", glm::value_ptr(view));
        shader.setUniformMatrix4f("projection", glm::value_ptr(projection));

        glBindVertexArray(VAO);
		
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

        timer.printFPS();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);

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
