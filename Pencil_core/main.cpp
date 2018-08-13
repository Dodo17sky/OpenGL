#include "TestWindow.h"

int main()
{
    TestWindow  app;

    app.init();
    app.createGui();
    
    while (!app.isClosing()) {
        app.getInput();

        app.draw();
        
        app.update();
    }

    return 0;
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    enum MouseState { UNKNOWN, PRESS_FIRST, PRESS, REPEAT, RELEASE  };
    static MouseState state = UNKNOWN;

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        //log("mouse-left down");
        //log(mods);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_REPEAT) {
        //log("mouse-left repeate");
        //log(mods);
    }

    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_RELEASE) {
        /*
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);

        xpos = ((xpos*2)/screenWidth - 1);
        ypos = screenHeight - ypos;
        ypos = ((ypos*2)/screenHeight - 1);

        const Pencil::Object2D* obj = renderer.getIntersectedObject(xpos, ypos);
        if (obj != nullptr) {
            std::cout << obj->getName() << std::endl;
        }
        */
    }
}

void processInput(GLFWwindow * win)
{
    /*
    if(glfwGetKey(win, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(win, 1);

    if(glfwGetKey(win, GLFW_KEY_P) == GLFW_PRESS)
        polygonMode = ((polygonMode==GL_FILL)?GL_LINE:GL_FILL);
     */
}
