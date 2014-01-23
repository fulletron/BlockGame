cmake_minimum_required (VERSION 2.6)

file(GLOB GRAPHICSSRC
    "*.h"
    "*.cpp"
)

add_library(Graphics ${GRAPHICSSRC} )

target_link_libraries(Graphics
		Entity
		Input
		Panel
		Resource
		State
		Utilities

		debug ${CMAKE_SOURCE_DIR}/External/libs/freetype2411_D.lib
		#debug ${CMAKE_SOURCE_DIR}/External/libs/sfml-system-s-d.lib
		#debug ${CMAKE_SOURCE_DIR}/External/libs/sfml-window-s-d.lib
		debug ${CMAKE_SOURCE_DIR}/External/libs/SOIL_deb.lib

		optimized ${CMAKE_SOURCE_DIR}/External/libs/freetype2411.lib
		#optimized ${CMAKE_SOURCE_DIR}/External/libs/sfml-system-s.lib
		#optimized ${CMAKE_SOURCE_DIR}/External/libs/sfml-window-s.lib
		optimized ${CMAKE_SOURCE_DIR}/External/libs/SOIL.lib

		${CMAKE_SOURCE_DIR}/External/libs/glfw.lib
		${CMAKE_SOURCE_DIR}/External/libs/glew32s.lib
		#${OPENGL_LIBRARIES}
)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )