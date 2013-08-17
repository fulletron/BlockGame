cmake_minimum_required (VERSION 2.6)

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

add_library( Utilities ${UTILITIESSRC} )

target_link_libraries( Utilities
		${BOOST_LIBRARIES}
)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )