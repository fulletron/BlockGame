cmake_minimum_required ( VERSION 2.6 )

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
	"input/*.h"
	"input/*.cpp"
	"time/*.h"
	"time/*.cpp"
	"filepath/*.h"
	"filepath/*.cpp"
	"thread/*.h"
	"thread/*.cpp"
	"commclient/*.h"
	"commclient/*.cpp"
	"commserver/*.h"
	"commserver/*.cpp"
)

## KYLE :: GroupSources CALL MAKES FOLDERS A THING IN VISUAL STUDIO! AWESOME!
GroupSources( ${CMAKE_CURRENT_SOURCE_DIR} "GENERAL" )

add_library( Utilities STATIC ${UTILITIESSRC} )

target_link_libraries( Utilities
	${OPENGL_LIBRARIES}
	GLEW
	glfw
	#SDL2main
	#SDL2-static
	# TEMP REM ${Boost_LIBRARIES}
	freetype
	SOIL
	Graphics
	Game
	Framework
)

add_library( UtilitiesTest ${UTILITIESSRC} )
target_link_libraries( UtilitiesTest
	${OPENGL_LIBRARIES}
	GLEW
	# TEMP REM ${Boost_LIBRARIES}
	glfw
	#SDL2main
	#SDL2-static
	freetype
	SOIL
)

#message( STATUS "glfw libs : " ${GLFW_LIBRARIES} )

SET_TARGET_PROPERTIES(UtilitiesTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET UtilitiesTest PROPERTY FOLDER "Test/Mirror")
