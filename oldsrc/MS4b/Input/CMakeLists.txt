cmake_minimum_required (VERSION 2.6)


file(GLOB INPUTSRC
    "*.h"
    "*.cpp"
)

add_library( Input ${INPUTSRC} )

target_link_libraries(Input
		Entity
		Resource)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )