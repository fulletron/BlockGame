cmake_minimum_required (VERSION 2.6)

file(GLOB GRAPHICSSRC
    "*.h"
    "*.cpp"
)

add_library( Graphics ${GRAPHICSSRC} )

target_link_libraries( Graphics
		${BOOST_LIBRARIES}
)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )