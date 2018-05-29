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

    glClearColor(1.0, 1.0, 0.8, 1.0);
    glViewport(0, 0, 480, 360);
    glfwSetFramebufferSizeCallback(window, resize_callback);

    Pencil::Shader shader("src/graphics/shaders/basic.vertex", "src/graphics/shaders/basic.fragment");
    shader.disable();

    //Define triangle coordinates
    float coords[] = {
        // Back
        /***      POSITION      /**	texture coords	*/
        /**/  0.0,  0.0, 0.0,   /**/	0.0, 0.0,	/**///	  0 - 0
        /**/  0.0,  1.0, 0.0,   /**/ 	0.0, 1.0,	/**///	  1 - 1
        /**/  1.0,  1.0, 0.0,   /**/ 	1.0, 1.0,	/**///	  2 - 2
        /**/  1.0,  0.0, 0.0,   /**/ 	1.0, 0.0, 	/**///	  3 - 3

        // Right
        /**/  1.0,  1.0, 0.0,   /**/ 	1.0, 1.0,	/**///	  2 - 4
        /**/  1.0,  0.0, 0.0,   /**/ 	1.0, 0.0, 	/**///	  3 - 5
        /**/  1.0,  0.0, 1.0,   /**/	0.0, 0.0,	/**///	  4 - 6
        /**/  1.0,  1.0, 1.0,   /**/ 	0.0, 1.0,	/**///	  5 - 7

        // Top
        /**/  0.0,  1.0, 0.0,   /**/ 	0.0, 0.0,	/**///	  1 - 8
        /**/  1.0,  1.0, 0.0,   /**/ 	1.0, 0.0,	/**///	  2 - 9
        /**/  1.0,  1.0, 1.0,   /**/ 	1.0, 1.0,	/**///	  5 - 10
        /**/  0.0,  1.0, 1.0,   /**/ 	0.0, 1.0,	/**///	  7 - 11

        // Left
        /**/  0.0,  0.0, 0.0,   /**/	1.0, 0.0,	/**///	  0 - 12
        /**/  0.0,  1.0, 0.0,   /**/ 	1.0, 1.0,	/**///	  1 - 13
        /**/  0.0,  1.0, 1.0,   /**/ 	0.0, 1.0,	/**///	  7 - 14
        /**/  0.0,  0.0, 1.0,   /**/ 	0.0, 0.0,	/**///	  6 - 15
        
        // Bottom
        /**/  0.0,  0.0, 0.0,   /**/	0.0, 1.0,	/**///	  0 - 16
        /**/  1.0,  0.0, 0.0,   /**/ 	1.0, 1.0, 	/**///	  3 - 17
        /**/  1.0,  0.0, 1.0,   /**/	1.0, 0.0,	/**///	  4 - 18
        /**/  0.0,  0.0, 1.0,   /**/ 	0.0, 0.0,	/**///	  6 - 19

        // Front
        /**/  0.0,  1.0, 1.0,   /**/ 	0.0, 1.0,	/**///	  7 - 20
        /**/  0.0,  0.0, 1.0,   /**/ 	0.0, 0.0,	/**///	  6 - 21
        /**/  1.0,  0.0, 1.0,   /**/	1.0, 0.0,	/**///	  4 - 22
        /**/  1.0,  1.0, 1.0,   /**/ 	1.0, 1.0	/**///	  5 - 23

    };
    GLuint indices[] = {
        0, 1, 2,
        0, 2, 3,
        4, 5, 6,
        4, 6, 7,
        8, 9, 10,
        8, 10, 11,
        12, 13, 14,
        12, 14, 15,
        16, 17, 18,
        16, 18, 19,
        20, 21, 22,
        20, 22, 23
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
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)12);
	glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 

    //Texture tex("image/container.jpg");
    Texture tex("image/timber.jpg");
    //Texture tex("image/container.jpg");
	tex.unbind();
	shader.enable();
	shader.setUniform1i("ourTexture", tex.getTextureSlot());


    Timer timer;
	timer.startCount();
	int i = 0;

    glm::mat4 model, view, projection;
    model = glm::translate(model, glm::vec3(-0.5f, -0.5f, -0.0f));
    model = glm::rotate(model, glm::radians(-45.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
    projection = glm::perspective(glm::radians(45.0f), screenWidth/screenHeight, 0.1f, 100.0f);

    glEnable(GL_DEPTH_TEST); 

    while (!glfwWindowShouldClose(window)) {

        processInput(window);
        
        if (timer.passed(0.02f)) {
            model = glm::rotate(model, glm::radians(1.0f), glm::vec3(0.5f, 1.0f, 1.0f));
            timer.startCount();
        }

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		tex.bind();
        

        shader.enable();
        shader.setUniformMatrix4f("model", glm::value_ptr(model));
        shader.setUniformMatrix4f("view", glm::value_ptr(view));
        shader.setUniformMatrix4f("projection", glm::value_ptr(projection));

        glBindVertexArray(VAO);
		
        glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

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
