#pragma once

#include "mainApp.h"
#include "graphics\Objects2D3D\geometrics\line.h"
#include "graphics\Objects2D3D\geometrics\Point.h"

class TestWindow : public MainWindow
{
    Pencil::Rectangle       *m_leftPanel;
    Pencil::Line            *m_leftLine;
    Pencil::Point           *m_points;
public:
    TestWindow();
    ~TestWindow();

    int         draw();
    int         createGui();

    friend static void resize_callback(GLFWwindow* win, int width, int height);
};

