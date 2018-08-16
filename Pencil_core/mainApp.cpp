#include "mainApp.h"

MainWindow::MainWindow(const char * title, GLfloat width, GLfloat height):
    m_window(nullptr)
    , m_shader(nullptr)
    , m_renderer(nullptr)
    , m_title(title)
    , m_winHeight(height)
    , m_winWidth(width)
{
    glfwInit(); 
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

    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    std::string title = "Main window";
    if(!m_title.empty())
        title = m_title;

    m_window = glfwCreateWindow( m_winWidth, m_winHeight, title.c_str(), NULL, NULL);
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
    glEnable(GL_DEPTH_TEST);

    m_shader = new Pencil::Shader("basic.vertex", "basic.fragment");
    m_shader->disable();

    m_renderer = new Pencil::Renderer();
    
    return 0;
}

int MainWindow::initMatrixMVP()
{
    m_model      = glm::mat4(1.0f);
    m_view       = glm::mat4(1.0f);
    m_projection = glm::mat4(1.0f);

    m_shader->enable();
    m_shader->setUniformMatrix4f("model", glm::value_ptr(m_model));
    m_shader->setUniformMatrix4f("view", glm::value_ptr(m_view));
    m_shader->setUniformMatrix4f("projection", glm::value_ptr(m_projection));

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

