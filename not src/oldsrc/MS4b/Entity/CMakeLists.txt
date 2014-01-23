cmake_minimum_required (VERSION 2.6)

file(GLOB ENTITYSRC
    "*.h"
    "*.cpp"
)

add_library(Entity ${ENTITYSRC})

target_link_libraries(Entity
		Utilities)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )