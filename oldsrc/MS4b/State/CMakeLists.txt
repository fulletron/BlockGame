cmake_minimum_required (VERSION 2.6)

file(GLOB STATESRC
    "*.h"
    "*.cpp"
)

add_library(State ${STATESRC} )

target_link_libraries(State
		Entity
		Input
		Panel
		Resource)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )