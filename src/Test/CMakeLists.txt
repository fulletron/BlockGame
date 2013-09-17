cmake_minimum_required (VERSION 2.6)

include_directories( ${CMAKE_SOURCE_DIR}/Main )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_subdirectory( UtilitiesTester )

set_property( GLOBAL PROPERTY USE_FOLDERS On)

SET_PROPERTY(TARGET UtilitiesTester PROPERTY FOLDER "Test")