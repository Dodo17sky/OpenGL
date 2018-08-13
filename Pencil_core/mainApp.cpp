#include "mainApp.h"

MainWindow::MainWindow(const char * title, GLfloat width, GLfloat height):
    m_window(nullptr)
    , m_shader(nullptr)
    , m_renderer(nullptr)
    , m_winHeight(height)
    , m_winWidth(width)
{
    glfwInit();

    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(
        m_winWidth, m_winHeight, 
        (title==nullptr)?"Main window":title, 
        NULL, NULL);
    if (m_window == NULL) {
        std::cout << "Failed to create GLFW window!" << std::endl;
        glfwTerminate();
        exit(-1);
    }
    glfwMakeContextCurrent(m_window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cout << "Failed to initilize GLAD" << std::endl;
        exit(-1);
    }
    else {
        std::cout << glGetString(GL_VERSION) << std::endl;
    }

    glClearColor(1.0, 1.0, 1.0, 1.0);
    glViewport(0, 0, m_winWidth, m_winHeight);
    
    glEnable(GL_DEPTH_TEST); 
}

MainWindow::~MainWindow()
{
    delete m_shader;
    delete m_renderer;
    delete m_window;
}

int MainWindow::init()
{
    int retCode = 0;

    m_shader = new Pencil::Shader("basic.vertex", "basic.fragment");
    m_shader->disable();

    m_renderer = new Pencil::Renderer();

    initMatrixMVP();

    return 0;
}

int MainWindow::initMatrixMVP()
{
    m_model      = glm::mat4();
    m_view       = glm::mat4();
    m_projection = glm::mat4();

    auto a = glm::value_ptr(m_model);

    m_shader->setUniformMatrix4f("model", a);

    return 0;
}

int MainWindow::uninit()
{
    glfwTerminate();
    return 0;
}

int MainWindow::getInput()
{
    return 0;
}

int MainWindow::update()
{
    glfwSwapBuffers(m_window);
    glfwPollEvents();

    return 0;
}

int MainWindow::draw()
{
    std::cout << "Clasa de baza\n";
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    return 0;
}

