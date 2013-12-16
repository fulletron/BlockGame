cmake_minimum_required (VERSION 2.6)

file(GLOB GAMESRC
    "*.h"
    "*.cpp"
)

add_executable(Game ${GAMESRC} )

target_link_libraries(Game
		Graphics
		Utilities
)

message(STATUS "Target File Dir :: " $<TARGET_FILE_DIR:Game>)

ADD_CUSTOM_COMMAND(TARGET Game
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Game>/Internal
          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Main/Internal $<TARGET_FILE_DIR:Game>/Internal
)
