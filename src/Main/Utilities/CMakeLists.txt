cmake_minimum_required ( VERSION 2.6 )

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

add_library( Utilities ${UTILITIESSRC} )
target_link_libraries( Utilities
	${OPENGL_LIBRARIES}
	#GLEW
	#${GLFW_LIBRARY}
	###${Boost_LIBRARY_DIR}
	${Boost_LIBRARIES}
	#glfw3
)

###include_directories( ${CMAKE_SOURCE_DIR} )
###include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_library( UtilitiesTest ${UTILITIESSRC} )
target_link_libraries( UtilitiesTest
	${OPENGL_LIBRARIES}
	#GLEW
	#${GLFW_LIBRARY}
	####${Boost_LIBRARY_DIR}
	${Boost_LIBRARIES}
	#glfw3
)

SET_TARGET_PROPERTIES(UtilitiesTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET UtilitiesTest PROPERTY FOLDER "Test/Mirror")
