cmake_minimum_required (VERSION 2.6)

#===============================
set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib)
set(BOOST_LIBRARYDIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib)
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)

find_package(Boost)
include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})

SET_PROPERTY(TARGET ${BOOST_LIBRARIES} PROPERTY FOLDER "External/Boost")
#===============================


file(GLOB GAMESRC
    "*.h"
    "*.cpp"
)

add_executable(Game ${GAMESRC} )

target_link_libraries(Game
		Utilities
		#Graphics
		${BOOST_LIBRARIES}
)

include_directories( ${CMAKE_SOURCE_DIR} )
#include_directories( ${CMAKE_SOURCE_DIR}/External/include )

ADD_CUSTOM_COMMAND(TARGET Game
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Game>/../Internal
          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Internal $<TARGET_FILE_DIR:Game>/../Internal
)
