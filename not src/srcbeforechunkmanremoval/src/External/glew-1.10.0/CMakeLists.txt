cmake_minimum_required (VERSION 2.6)

file(GLOB GLEWSRC
    "src/*.c"
)

include_directories( ${CMAKE_SOURCE_DIR}/Main )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_library(GLEW ${GLEWSRC} )

target_link_libraries(GLEW ${OPENGL_LIBRARIES})

SET_PROPERTY(TARGET GLEW                    PROPERTY FOLDER "External/GLEW")
