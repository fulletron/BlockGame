cmake_minimum_required (VERSION 2.6)

file(GLOB SOILSRC
    "original/*.h"
    "original/*.cpp"
    "original/*.c"
    "*.h"
    "*.cpp"
    "*.c"
)

add_library(SOIL ${SOILSRC} )

SET_PROPERTY(TARGET SOIL                    PROPERTY FOLDER "External/SOIL")