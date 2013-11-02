cmake_minimum_required ( VERSION 2.6 )

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

#find_library( GLFW_LIBRARY NAMES glfw3
#	HINTS 
#	${CMAKE_BINARY_DIR}/External/glfw-3.0.2/src/Release )
#set( GLFW_LIBRARY glfw3 )

#find_library( GLEW_LIBRARY NAMES GLEW
#	HINTS 
#	${CMAKE_BINARY_DIR}/External/glew-1.10.0/Release )
set( GLEW_LIBRARY GLEW )

find_package(OpenGL)
if (OPENGL_FOUND)
    MESSAGE("OpenGL Correctly Found")
    #include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
    MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)

message( STATUS "GLFW OUT DIR:: " ${CMAKE_BINARY_DIR}/src/ )
message( STATUS "OPENGL LIBS:: " ${GLEW_LIBRARY} )

add_library( Utilities ${UTILITIESSRC} )
target_link_libraries( Utilities
	${OPENGL_LIBRARIES}
	#${GLEW_LIBRARY}
	#${GLFW_LIBRARY}
	${Boost_LIBRARIES}
	glfw
)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_library( UtilitiesTest ${UTILITIESSRC} )
target_link_libraries( UtilitiesTest
	${OPENGL_LIBRARIES}
	#${GLEW_LIBRARY}
	#${GLFW_LIBRARY}
	${Boost_LIBRARIES}
	glfw
)

SET_TARGET_PROPERTIES(UtilitiesTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET UtilitiesTest PROPERTY FOLDER "Test/Mirror")
