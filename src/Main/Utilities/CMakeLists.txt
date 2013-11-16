cmake_minimum_required ( VERSION 2.6 )

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

add_library( Utilities ${UTILITIESSRC} )

target_link_libraries( Utilities
	${OPENGL_LIBRARIES}
	GLEW
	glfw
	${Boost_LIBRARIES}
)

add_library( UtilitiesTest ${UTILITIESSRC} )
target_link_libraries( UtilitiesTest
	${OPENGL_LIBRARIES}
	GLEW
	${Boost_LIBRARIES}
	glfw
)

message( STATUS "glfw libs : " ${GLFW_LIBRARIES} )

SET_TARGET_PROPERTIES(UtilitiesTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET UtilitiesTest PROPERTY FOLDER "Test/Mirror")
