cmake_minimum_required (VERSION 2.6)

file(GLOB GRAPHICSSRC
    "*.h"
    "*.cpp"
)

add_library( Graphics ${GRAPHICSSRC} )
target_link_libraries( Graphics
		Utilities
)

###include_directories( ${CMAKE_SOURCE_DIR} )
###include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_library( GraphicsTest ${GRAPHICSSRC} )
target_link_libraries( GraphicsTest
		UtilitiesTest
)

SET_TARGET_PROPERTIES(GraphicsTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET GraphicsTest PROPERTY FOLDER "Test/Mirror")