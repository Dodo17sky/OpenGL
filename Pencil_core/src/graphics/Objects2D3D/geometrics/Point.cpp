#include "Point.h"

namespace Pencil {

    int Point::m_count = 0;
    
    Point::Point(Shader * shader):
        m_Points(0)
        , m_PointsCount(0)
        , m_PointSize(1.0f)
        , Object2D(glm::vec3(0.0f, 0.0f, 0.0f), glm::vec2(1.0f, 1.0f), shader, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f))
    {
        std::string name = "def_point_" + std::to_string(m_count);
        setName(name);
        m_count++;
    }

    Point::~Point()
    {
    }

    void Point::draw()
    {
        m_Shader->enable();
        m_VAO->bind();
        m_EBO->bind();

        glPointSize(m_PointSize);
        glDrawElements(GL_POINTS, m_EBO->getCount(), GL_UNSIGNED_SHORT, nullptr);
        glPointSize(1.0);

        m_Shader->disable();
        m_VAO->unbind();
        m_EBO->unbind();
    }

    void Point::addPoints(const glm::vec3 * data, unsigned int count)
    {
        m_PointsCount = count;
        m_Points = std::vector<glm::vec3>();
        m_Points.reserve(count);
        while (count--) {
            m_Points.push_back(glm::vec3(*data));
            data++;
        }
        createPoint();
    }

    void Point::createPoint()
    {
        delete m_VAO;
        delete m_EBO;

        GLfloat *vertices = new GLfloat[m_PointsCount*3];
        for (int i = 0; i < m_PointsCount; i++) {
            vertices [0 + (i*3)] = m_Points[i].x;
            vertices [1 + (i*3)] = m_Points[i].y;
            vertices [2 + (i*3)] = m_Points[i].z;
        }

        GLfloat *colors = new GLfloat[m_PointsCount*4];
        for (int i = 0; i < m_PointsCount; i++) {
            colors [0 + (i*4)] = m_Color.r;
            colors [1 + (i*4)] = m_Color.g;
            colors [2 + (i*4)] = m_Color.b;
            colors [3 + (i*4)] = m_Color.a;
        }

        GLushort *indices = new GLushort[m_PointsCount*4];
        for (int i = 0; i < m_PointsCount; i++) {
            indices[i] = i;
        }

        m_VAO = new VertexArray();
        m_EBO = new IndexBuffer(indices, m_PointsCount);

        Buffer* vBuf = new Buffer(vertices, m_PointsCount*3, 3);
        Buffer* cBuf = new Buffer(colors, m_PointsCount*4, 4);

        m_VAO->addBuffer(vBuf, 0);
        m_VAO->addBuffer(cBuf, 1);

        delete vBuf, cBuf;
        delete[] vertices;
        delete[] colors;
        delete[] indices;
    }
}