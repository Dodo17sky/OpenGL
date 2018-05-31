#include <iostream>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "src\graphics\textures\texture.h"
#include "src\graphics\shaders\shader.h"
#include "src\utils\Timer.h"
#include "ext\stb_image\stb_image.h"

#include "src\graphics\buffers\vertexarray.h"
#include "src\graphics\buffers\buffer.h"

#include "src\graphics\Objects2D3D\Object2D.h"
#include "src\graphics\Objects2D3D\Renderer.h"
#include "src\graphics\Objects2D3D\geometrics\rectangle.h"

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp";

// callbacks
void resize_callback(GLFWwindow* win, int width, int height);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

// static functions
void processInput(GLFWwindow* win);

void all_inits();

// Global variables
GLenum polygonMode = GL_FILL;
GLFWwindow* window;
Pencil::Renderer renderer;

#define log(x) std::cout << x << std::endl

#define screenWidth     480.0f
#define screenHeight    360.0f

int main()
{
    using namespace Pencil;
    all_inits();

    Pencil::Shader shader("src/graphics/shaders/basic.vertex", "src/graphics/shaders/basic.fragment");
    shader.disable();

#define color_Blue  glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
#define color_Red   glm::vec4(1.0f, 0.0f, 0.0f, 1.0f)

    Pencil::Rectangle rec1(glm::vec3(-0.8, -0.6,0), glm::vec2(0.5, 0.5), &shader, color_Blue);
    rec1.setFillType(Rectangle::RECTYPE_EMPTY);
    rec1.setLineWidth(5);
    rec1.setName("Blue");
    Pencil::Rectangle rec2(glm::vec3(-1.0,-1.0,0), glm::vec2(0.2, 0.2), &shader, color_Red);
    rec2.setFillType(Rectangle::RECTYPE_EMPTY);
    rec2.setLineWidth(1);
    rec2.setName("Red");

    renderer.add(&rec2);
    renderer.add(&rec1);

    while (!glfwWindowShouldClose(window)) {
        processInput(window);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        renderer.draw();
        
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

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    enum MouseState { UNKNOWN, PRESS_FIRST, PRESS, REPEAT, RELEASE  };
    static MouseState state = UNKNOWN;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        log("mouse-left down");
        log(mods);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_REPEAT) {
        log("mouse-left repeate");
        log(mods);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        xpos = ((xpos*2)/screenWidth - 1);
        ypos = screenHeight - ypos;
        ypos = ((ypos*2)/screenHeight - 1);

        const Pencil::Object2D* obj = renderer.getIntersectedObject(xpos, ypos);
        if (obj != nullptr) {
            std::cout << obj->getName() << std::endl;
        }
    }
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
	glfwSetMouseButtonCallback(window, mouse_button_callback);
    glEnable(GL_DEPTH_TEST); 
}