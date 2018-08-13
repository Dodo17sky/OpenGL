#include "TestWindow.h"



TestWindow::TestWindow():
    //MainWindow("Test window", 300, 100)
    //MainWindow("Test window")
    MainWindow()
    , m_rec1(nullptr)
{
    MainWindow::init();

    createGui();
}


TestWindow::~TestWindow()
{
    delete m_rec1;
}

int TestWindow::draw()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    m_renderer->add(m_rec1);

    m_renderer->draw();
    
    return 0;
}

int TestWindow::createGui()
{
    m_rec1 = new Pencil::Rectangle(glm::vec3(0.0f, 0.0f,0.0f), glm::vec2(0.5f, 0.5f), m_shader, GL_COLOR_BLUE);
    m_rec1->setLineWidth(1.0f);
    m_rec1->setFillType(Pencil::Rectangle::RECTYPE_EMPTY);

    return 0;
}
