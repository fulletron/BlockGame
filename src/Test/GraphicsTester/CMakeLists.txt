cmake_minimum_required (VERSION 2.6)

file(GLOB GRAPHICSTESTERSRC
    "*.h"
    "*.cpp"
)

add_executable( GraphicsTester ${GRAPHICSTESTERSRC} )

target_link_libraries( GraphicsTester
		GraphicsTest
		GTEST
)
