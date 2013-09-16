cmake_minimum_required (VERSION 2.6)

file(GLOB UTILITIESTESTSRC
    "*.h"
    "*.cpp"
)

add_executable( UtilitiesTest ${UTILITIESTESTSRC} )

target_link_libraries( UtilitiesTest
		Utilities
		GTEST
)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )
