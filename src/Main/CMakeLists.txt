cmake_minimum_required (VERSION 2.6)

include_directories( ${CMAKE_SOURCE_DIR}/Main )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_subdirectory( Game )
add_subdirectory( Graphics )
add_subdirectory( Utilities )

set_property( GLOBAL PROPERTY USE_FOLDERS On)

SET_PROPERTY(TARGET Game PROPERTY FOLDER "Main")
SET_PROPERTY(TARGET Utilities PROPERTY FOLDER "Main")
SET_PROPERTY(TARGET Graphics PROPERTY FOLDER "Main")
