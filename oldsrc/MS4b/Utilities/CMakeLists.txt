cmake_minimum_required (VERSION 2.6)

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

add_library(Utilities ${UTILITIESSRC} )

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )