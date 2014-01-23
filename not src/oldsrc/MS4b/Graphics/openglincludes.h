#pragma once

#ifndef __OPENGLINCLUDES_H_
#define __OPENGLINCLUDES_H_

#define GLEW_STATIC
#define SFML_STATIC

#pragma warning( disable : 4005 )

#include "gl\glew.h"
#include "gl\glfw.h"
#include "gl\GL.h"

#include "SFML\Window.hpp"

#include "SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ft2build.h"
#include FT_FREETYPE_H

#endif