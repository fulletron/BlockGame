cmake_minimum_required (VERSION 2.6)

file(GLOB RESOURCESRC
    "base/*.h"
    "base/*.cpp"
    "constructs/*.h"
    "constructs/*.cpp"
)

add_library(Resource ${RESOURCESRC} )

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )