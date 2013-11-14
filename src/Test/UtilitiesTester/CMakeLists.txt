cmake_minimum_required (VERSION 2.6)

file(GLOB UTILITIESTESTERSRC
    "*.h"
    "*.cpp"
)

add_executable( UtilitiesTester ${UTILITIESTESTERSRC} )

target_link_libraries( UtilitiesTester
		UtilitiesTest
		GTEST
)
