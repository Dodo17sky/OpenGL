#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "src\graphics\shaders\shader.h"
#include "src\utils\Timer.h"
#include "ext\stb_image\stb_image.h"

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);

// static functions
void processInput(GLFWwindow* win);

// Global variables
GLenum polygonMode = GL_FILL;

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
        /***      POSITION      /**         COLOR          /**	texture coords	*/
        /**/ -0.7, -0.7, 0.0,   /**/    1.0f, 0.0f, 0.0f,  /**/		0.0, 0.0,	/**///	bottom left
        /**/ -0.7,  0.7, 0.0,   /**/    0.0f, 1.0f, 0.0f,  /**/ 	0.0, 2.0,	/**///	top left
        /**/  0.7,  0.7, 0.0,   /**/    1.0f, 0.0f, 0.0f,  /**/ 	2.0, 2.0,	/**///	top right	
        /**/  0.7, -0.7, 0.0,   /**/    0.0f, 1.0f, 0.0f,  /**/ 	2.0, 0.0 	/**///	bottom right
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

	int imgWidth, imgHeight, imgNmbChn;
	unsigned char* imgBuf = stbi_load("container.jpg", &imgWidth, &imgHeight, &imgNmbChn, 0);
	unsigned int textureId1, textureId2;
	glGenTextures(1, &textureId1);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, textureId1);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (imgBuf) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, imgBuf);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else{
		std::cout << "Failed to load image texture" << std::endl;
	}
	stbi_image_free(imgBuf);

	stbi_set_flip_vertically_on_load(true);
	imgBuf = stbi_load("awesomeface.png", &imgWidth, &imgHeight, &imgNmbChn, 0);
	glGenTextures(1, &textureId2);
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, textureId2);
	// set the texture wrapping/filtering options (on the currently bound texture object)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	if (imgBuf) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, imgWidth, imgHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, imgBuf);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Failed to load image texture" << std::endl;
	}
	stbi_image_free(imgBuf);

	shader.enable();
	shader.setUniform1i("ourTexture1", 0);
	shader.setUniform1i("ourTexture2", 1);

    Timer timer;
    timer.startCount();
    float off = -0.3;
    float step = 0.01;

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT);

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, textureId1);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, textureId2);

        shader.enable();
        glBindVertexArray(VAO);

        if (timer.getElapsedTime() > 0.01) {
            shader.setUniform1f("offset", off);
			if (off > 0.3) {
				step = -0.01;
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			}
			if (off < -0.3) {
				step = 0.01;
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
			}
            
            off += step;
            timer.startCount();
        }

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
