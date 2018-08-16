#pragma once

#include "mainApp.h"
#include "graphics\Objects2D3D\geometrics\line.h"

class TestWindow : public MainWindow
{
    Pencil::Rectangle       *m_leftPanel;
    Pencil::Line            *m_leftLine;
public:
    TestWindow();
    ~TestWindow();

    int         draw();
    int         createGui();

    friend static void resize_callback(GLFWwindow* win, int width, int height);
};

