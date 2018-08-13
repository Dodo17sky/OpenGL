#pragma once

#include "mainApp.h"

class TestWindow : public MainWindow
{
    Pencil::Rectangle       *m_rec1;
public:
    TestWindow();
    ~TestWindow();

    int         draw();
    int         createGui();
};

