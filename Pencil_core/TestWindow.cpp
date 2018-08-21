#include "TestWindow.h"

TestWindow::TestWindow():
    MainWindow("Test window", 600, 350)
    //MainWindow("Test window")
    , m_leftPanel(nullptr)
    , m_leftLine(nullptr)
    , m_points(nullptr)
{
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    MainWindow::init();
    glfwSetWindowUserPointer(m_window, this);
    glViewport(0,0, DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT);

    // set event callback functions
    glfwSetFramebufferSizeCallback(m_window, resize_callback);
}

TestWindow::~TestWindow()
{
    delete m_leftPanel;
    delete m_leftLine;
    delete m_points;
}

int TestWindow::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_shader->enable();
    m_shader->setUniformMatrix4f("MVP", glm::value_ptr(m_MVP));

    m_renderer->add(m_leftLine);
    m_renderer->add(m_leftPanel);
    m_renderer->add(m_points);

    m_renderer->draw();
    
    return 0;
}

int TestWindow::createGui()
{
    m_view = glm::lookAt(
        glm::vec3(0,0,5), // Camera is at (0,0,5), in World Space
        glm::vec3(0,0,0), // and looks at the origin
        glm::vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
    );
    m_model = glm::mat4(1.0f);
    m_projection = glm::ortho( 0.0f, m_winWidth, 0.0f, m_winHeight, -1.0f, 15.0f);
    m_MVP = m_projection * m_view * m_model;

    m_leftPanel = new Pencil::Rectangle(
        glPosition(0.0f, 0.0f,0.0f), 
        glSize(250.0f, m_winHeight), 
        m_shader, 
        GL_COLOR_LIGHT_BROWN);
    m_leftPanel->setLineWidth(1.0f);
    m_leftPanel->setFillType(Pencil::Rectangle::RECTYPE_FILLED);

    m_leftLine = new Pencil::Line(
        glPosition(250.0f, 0.0f,0.0f), 
        glm::vec2(250.0f, m_winHeight),
        m_shader, 
        GL_COLOR_BLACK);
    m_leftLine->setLineWidth(3.0f);

    glm::vec3 pts[] = {
        {300.0f,  50.0f, 0.0f},
        {350.0f, 100.0f, 0.0f},
        {400.0f, 150.0f, 0.0f},
        {450.0f, 200.0f, 0.0f},
        {500.0f, 150.0f, 0.0f},
        {550.0f, 100.0f, 0.0f}
    };
    m_points = new Pencil::Point(m_shader);
    m_points->setColor(GL_COLOR_GREEN);
    m_points->setPointSize(5.0f);
    m_points->addPoints(pts,6);

    return 0;
}

void resize_callback(GLFWwindow * win, int width, int height)
{
    TestWindow* obj = (TestWindow*)glfwGetWindowUserPointer(win);
    obj->m_winWidth  = width;
    obj->m_winHeight = height;
    //glViewport(0, 0, width, height);
    glViewport(0,0, DEFAULT_WIN_WIDTH, DEFAULT_WIN_HEIGHT);
}
