cmake_minimum_required ( VERSION 2.6 )

# set( Boost_USE_STATIC_LIBS ON )
# set( Boost_USE_MULTITHREADED ON )
# set( Boost_USE_STATIC_RUNTIME ON )

# if(WIN32)
	# set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib)
	# set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
	# set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
	
	# find_package(Boost)
	# include_directories(${Boost_INCLUDE_DIR})
	# link_directories(${Boost_LIBRARY_DIR})	
	# message(TEST:: WIN32)
	
	## //SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/External/include/boost")
	## //SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib")
	
# elseif(APPLE)
	# message(TEST:: APPLE)
# else()
	# find_package( Boost 1.54.0 COMPONENTS system regex filesystem atomic chrono )
	# message(TEST:: UNIX)
# endif()


#FIND_PACKAGE(Boost)
#IF (Boost_FOUND)
#    INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIR})
#    ADD_DEFINITIONS( "-DHAS_BOOST" )
#ENDIF()

#set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib)
#set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
#set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)

#find_package(Boost)
#include_directories(${Boost_INCLUDE_DIR})
#link_directories(${Boost_LIBRARY_DIR})

#SET_PROPERTY(TARGET ${Boost_LIBRARIES} PROPERTY FOLDER "External/Boost")

file(GLOB UTILITIESSRC
    "*.h"
    "*.cpp"
)

add_library( Utilities ${UTILITIESSRC} )

target_link_libraries( Utilities
	${Boost_LIBRARIES}
)

include_directories( ${CMAKE_SOURCE_DIR} )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

add_library( UtilitiesTest ${UTILITIESSRC} )
target_link_libraries( UtilitiesTest
	${Boost_LIBRARIES}
)

SET_TARGET_PROPERTIES(UtilitiesTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET UtilitiesTest PROPERTY FOLDER "Test/Mirror")
