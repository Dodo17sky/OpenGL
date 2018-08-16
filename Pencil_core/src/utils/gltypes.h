#pragma once

#include "glm\glm.hpp"


typedef     glm::vec2               glSize;
typedef     glm::vec3               glPosition;
typedef     glm::vec4               glColor;
typedef     glm::mat4               glMatModel;
typedef     glm::mat4               glMatView;
typedef     glm::mat4               glMatProjection;


#define SU(x)                       (x/255.0f)                               // SU = Sub Unitar. Convert color value from 0-255 to 0.0-1.0
#define GL_COLOR_BLACK              glColor(0.0f, 0.0f, 0.0f, 1.0f)
#define GL_COLOR_RED                glColor(1.0f, 0.0f, 0.0f, 1.0f)
#define GL_COLOR_GREEN              glColor(0.0f, 1.0f, 0.0f, 1.0f)
#define GL_COLOR_BLUE               glColor(0.0f, 0.0f, 1.0f, 1.0f)
#define GL_COLOR_LIGHT_BROWN        glColor(SU(225), SU(225), SU(208), 1.0f)
