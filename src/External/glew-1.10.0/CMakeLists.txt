cmake_minimum_required (VERSION 2.6)

file(GLOB GLEWSRC
    "src/*.c"
)

add_library(GLEW ${GLEWSRC} )

include_directories( ${CMAKE_CURRENT_LIST_DIR}/../include )

target_link_libraries(GLEW ${OPENGL_LIBRARIES})

SET_PROPERTY(TARGET GLEW                    PROPERTY FOLDER "External/GLEW")