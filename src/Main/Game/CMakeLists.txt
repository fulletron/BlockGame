cmake_minimum_required (VERSION 2.6)

file(GLOB GAMESRC
    "*.h"
    "*.cpp"
)

#maybe this will help?
GroupSources( ${CMAKE_CURRENT_SOURCE_DIR} "GENERAL" )	

add_library( Game ${GAMESRC} )
target_link_libraries( Game
		Graphics
		Utilities
)

#message(STATUS "Target File Dir :: " $<TARGET_FILE_DIR:Launchpad>)

#ADD_CUSTOM_COMMAND(TARGET Game
#          POST_BUILD
#          COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Game>/Resources
#          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Main/Resources $<TARGET_FILE_DIR:Game>/Resources
#)
