cmake_minimum_required (VERSION 2.6)

include_directories( ${CMAKE_SOURCE_DIR}/Main )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_subdirectory( Game )

set_property( GLOBAL PROPERTY USE_FOLDERS On)

SET_PROPERTY(TARGET Game PROPERTY FOLDER "Main")