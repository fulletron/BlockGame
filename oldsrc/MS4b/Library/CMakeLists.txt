cmake_minimum_required (VERSION 2.6)

file(GLOB LIBRARYSRC
    "*.h"
    "*.cpp"
)

add_library(Library ${LIBRARYSRC} )

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )
