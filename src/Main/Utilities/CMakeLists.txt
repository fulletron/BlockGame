cmake_minimum_required ( VERSION 2.6 )

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

##GroupSources( ${CMAKE_CURRENT_SOURCE_DIR} "GENERAL" )

add_library( Utilities ${UTILITIESSRC} )

target_link_libraries( Utilities
	${OPENGL_LIBRARIES}
	GLEW
	glfw
	${Boost_LIBRARIES}
	freetype
	SOIL
)

add_library( UtilitiesTest ${UTILITIESSRC} )
target_link_libraries( UtilitiesTest
	${OPENGL_LIBRARIES}
	GLEW
	${Boost_LIBRARIES}
	glfw
	freetype
	SOIL
)

message( STATUS "glfw libs : " ${GLFW_LIBRARIES} )

SET_TARGET_PROPERTIES(UtilitiesTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET UtilitiesTest PROPERTY FOLDER "Test/Mirror")
