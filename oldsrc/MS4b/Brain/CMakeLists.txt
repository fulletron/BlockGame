cmake_minimum_required (VERSION 2.6)

file(GLOB BRAINSRC
    "*.h"
    "*.cpp"
)

add_library(Brain ${BRAINSRC} )

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )
