cmake_minimum_required (VERSION 2.6)

file(GLOB GLFW_TESTSRC
    "*.h"
    "*.cpp"
)

#UNSURE WHAT THIS DOES
GroupSources( ${CMAKE_CURRENT_SOURCE_DIR} "GENERAL" )	

add_executable(GLFW_Test ${GLFW_TESTSRC} )

target_link_libraries( GLFW_Test
	${OPENGL_LIBRARIES}
	GLEW
	glfw
	#SDL2main
	#SDL2-static
	# TEMP REM ${Boost_LIBRARIES}
	freetype
	SOIL
)

message(STATUS "Target File Dir :: " $<TARGET_FILE_DIR:GLFW_Test>)

ADD_CUSTOM_COMMAND(TARGET GLFW_Test
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:GLFW_Test>/Textures
          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/GLFW_Test/Textures $<TARGET_FILE_DIR:GLFW_Test>/Textures
)
