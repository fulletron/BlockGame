cmake_minimum_required (VERSION 2.6)

file(GLOB GLEWSRC
    "src/*.c"
)

add_library(GLEW ${GLEWSRC} )

include_directories( ${CMAKE_SOURCE_DIR}/External/include )

find_package(OpenGL)
if (OPENGL_FOUND)
    MESSAGE("OpenGL Correctly Found")
    #include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
    MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)

target_link_libraries(GLEW ${OPENGL_LIBRARIES})

SET_PROPERTY(TARGET GLEW                    PROPERTY FOLDER "External/GLEW")