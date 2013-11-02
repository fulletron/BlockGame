cmake_minimum_required (VERSION 2.8)
project( Main )

add_definitions(-D_VARIADIC_MAX=10)

include_directories( ${CMAKE_SOURCE_DIR}/Main )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
	set(TARGET_OS windows)
	# set(LIB_PREFIX )
	if(CMAKE_SIZEOF_VOID_P MATCHES "4") 
		set(ARCH_BITS 32)
	elseif(CMAKE_SIZEOF_VOID_P MATCHES "8")
		set(ARCH_BITS 64)
	endif()
	set(STATIC_LIB_SUFFIX  .lib)
	set(DYANMIC_LIB_SUFFIX .dll) 
elseif(ANDROID)
	set(TARGET_OS android)
	set(LIB_PREFIX lib)
	set(STATIC_LIB_SUFFIX  .a)
	set(DYANMIC_LIB_SUFFIX .so) 
elseif(APPLE)
	set(TARGET_OS darwin)
	set(LIB_PREFIX lib)
	set(STATIC_LIB_SUFFIX  .a)
	set(DYANMIC_LIB_SUFFIX .dylib) 
add_definitions(-g)
else()
	set(TARGET_OS linux)
	set(LIB_PREFIX lib)
	set(STATIC_LIB_SUFFIX  .a)
	set(DYANMIC_LIB_SUFFIX .so) 

	add_definitions(-g)
	add_definitions(-DGTEST_HAS_PTHREAD=0)
endif()

#]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]]

set( Boost_USE_STATIC_LIBS ON )
set( Boost_USE_MULTITHREADED ON )
set( Boost_USE_STATIC_RUNTIME ON )

if(WIN32)
	set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib)
	set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
	set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
	
	find_package(Boost)
	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIR})	
	message(TEST:: WIN32)
	
	#SET(CMAKE_INCLUDE_PATH ${CMAKE_INCLUDE_PATH} "${CMAKE_SOURCE_DIR}/External/include/boost")
	#SET(CMAKE_LIBRARY_PATH ${CMAKE_LIBRARY_PATH} "${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib")
	
elseif(APPLE)
	message(TEST:: APPLE)
else()
	set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0/stage/lib)
	set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
	set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/External/boost_1_54_0)
	
	find_package(Boost)
	include_directories(${Boost_INCLUDE_DIR})
	link_directories(${Boost_LIBRARY_DIR})

	#find_package( Boost 1.54.0 COMPONENTS system regex filesystem atomic chrono thread)
	message(TEST:: UNIX)
endif()

#[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[[


#========================================
find_package(OpenGL)
if (OPENGL_FOUND)
    MESSAGE("OpenGL Correctly Found")
    #include_directories(${OPENGL_INCLUDE_DIR})
else (OPENGL_FOUND)
    MESSAGE("OpenGL environment missing")
endif (OPENGL_FOUND)
#========================================


if(APPLE)
	# On Mac systems, we need to explicitly enable C++11 extensions and runtime
	#set(CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++")
	set(CMAKE_CXX_FLAGS "-std=c++0x" )
elseif(WIN32)
else()
	#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x" )
	set(CMAKE_CXX_FLAGS "-std=c++0x -Wno-write-strings -L/GitRepos/BlockGame/src/External/boost_1_54_0/stage/lib -I/GitRepos/BlockGame/src/External/boost_1_54_0" )
endif()

add_subdirectory( External )
add_subdirectory( Main )
add_subdirectory( Test )
