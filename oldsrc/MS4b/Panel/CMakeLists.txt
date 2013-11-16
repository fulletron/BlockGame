cmake_minimum_required (VERSION 2.6)

file(GLOB PANELSRC
    "base/*.h"
    "base/*.cpp"
    "implementedpanels/*.h"
    "implementedpanels/*.cpp"
)

add_library(Panel ${PANELSRC} )

target_link_libraries(Panel
		Entity
		Input
		Resource)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )