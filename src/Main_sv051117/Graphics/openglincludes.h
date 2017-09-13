#pragma once

#ifndef __OPENGLINCLUDES_H_
#define __OPENGLINCLUDES_H_

#define GLEW_STATIC
#include "gl/glew.h"
#include "gl/GL.h"
#pragma warning( disable : 4005 )

//#define USING_SDL
#define USING_GLFW

#ifdef USING_SDL
#include "SDL/SDL.h"
// Apparently, SDL needs to redefine main to inject itself 
// for the purpose of initializing before running your code.
// HOWEVER, this causes all sorts of linking errors with
// glew.h. By undefining this definition, nothing actually breaks
// (according to the internets).
#undef main
/*
#include "SDL/SDL_main.h"
#include "SDL/SDL_stdinc.h"
#include "SDL/SDL_assert.h"
#include "SDL/SDL_atomic.h"
#include "SDL/SDL_audio.h"
#include "SDL/SDL_clipboard.h"
#include "SDL/SDL_cpuinfo.h"
#include "SDL/SDL_endian.h"
#include "SDL/SDL_error.h"
#include "SDL/SDL_events.h"
#include "SDL/SDL_filesystem.h"
#include "SDL/SDL_joystick.h"
#include "SDL/SDL_gamecontroller.h"
#include "SDL/SDL_haptic.h"
#include "SDL/SDL_hints.h"
#include "SDL/SDL_loadso.h"
#include "SDL/SDL_log.h"
#include "SDL/SDL_messagebox.h"
#include "SDL/SDL_mutex.h"
#include "SDL/SDL_power.h"
#include "SDL/SDL_render.h"
#include "SDL/SDL_rwops.h"
#include "SDL/SDL_system.h"
#include "SDL/SDL_thread.h"
#include "SDL/SDL_timer.h"
#include "SDL/SDL_version.h"
#include "SDL/SDL_video.h"
*/

#endif
#ifdef USING_GLFW
#include "GLFW/glfw3.h"
#endif

#include "SOIL.h"

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "ft2build.h"
#include "freetype/freetype.h"
#include "freetype/ftglyph.h"
#include FT_FREETYPE_H

#endif