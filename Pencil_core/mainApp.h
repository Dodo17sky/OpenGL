#pragma once

#include <iostream>
#include <string>

#include "glad\glad.h"
#include "GLFW\glfw3.h"

#include "graphics\textures\texture.h"
#include "graphics\shaders\shader.h"
#include "utils\Timer.h"
#include "stb_image\stb_image.h"

#include "graphics\buffers\vertexarray.h"
#include "graphics\buffers\buffer.h"

#include "graphics\Objects2D3D\Object2D.h"
#include "graphics\Objects2D3D\Renderer.h"
#include "graphics\Objects2D3D\geometrics\rectangle.h"

#include "utils\gltypes.h"
#include "glm\gtc\matrix_transform.hpp"
#include "glm\gtc\type_ptr.hpp";

#define     DEFAULT_WIN_HEIGHT          360
#define     DEFAULT_WIN_WIDTH           480

class MainWindow
{
protected:
    GLFWwindow                  *m_window;
    Pencil::Shader              *m_shader;
    Pencil::Renderer            *m_renderer;
    std::string                 m_title;
    glMatModel                  m_model;
    glMatView                   m_view;
    glMatProjection             m_projection;
    glm::mat4                   m_MVP;
    GLfloat                     m_winHeight;
    GLfloat                     m_winWidth;

public:
    explicit MainWindow(const char *title = nullptr, GLfloat width = DEFAULT_WIN_WIDTH, GLfloat height = DEFAULT_WIN_HEIGHT);
    ~MainWindow();

    int                         init();
    int                         uninit();
    bool                        isClosing() const   { return glfwWindowShouldClose(m_window); }
    int                         getInput();
    int                         update();
    virtual int                 draw();

    inline Pencil::Shader*      getShader() const   { return m_shader; }
    inline Pencil::Renderer*    getRenderer() const   { return m_renderer; }

public:
    int                         initMatrixMVP();
};

