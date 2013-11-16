cmake_minimum_required (VERSION 2.8)
project( Main )

add_definitions(-D_VARIADIC_MAX=10)

include_directories( ${CMAKE_SOURCE_DIR}/Main )
include_directories( ${CMAKE_SOURCE_DIR}/External/include )

SET_PROPERTY(GLOBAL PROPERTY USE_FOLDERS ON)

if(WIN32)
	message(TEST:: WIN32)
	set(TARGET_OS windows)
	# set(LIB_PREFIX )
	if(CMAKE_SIZEOF_VOID_P MATCHES "4") 
		set(ARCH_BITS 32)
	elseif(CMAKE_SIZEOF_VOID_P MATCHES "8")
		set(ARCH_BITS 64)
	endif()
	set(STATIC_LIB_SUFFIX  .lib)
	set(DYANMIC_LIB_SUFFIX .dll) 
elseif(APPLE)
	message(TEST:: APPLE)
	set(TARGET_OS darwin)
	set(LIB_PREFIX lib)
	set(STATIC_LIB_SUFFIX  .a)
	set(DYANMIC_LIB_SUFFIX .dylib) 
	add_definitions(-g)
else()
	message(TEST:: UNIX)
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
set( Boost_USE_STATIC_RUNTIME OFF )

###set( Boost_DEBUG ON )

set(Boost_LIBRARY_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_55_0/stage/lib)
set(BOOST_LIBRARYDIR ${CMAKE_SOURCE_DIR}/External/boost_1_55_0/stage/lib)
set(Boost_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/External/boost_1_55_0)
set(BOOST_ROOT ${CMAKE_SOURCE_DIR}/External/boost_1_55_0)

if(WIN32)
    find_package( Boost 1.55.0 COMPONENTS system regex filesystem atomic chrono thread timer date_time REQUIRED )
elseif(APPLE)
    find_package(Boost)
else()
    add_definitions( -DBOOST_ALL_NO_LIB )
    find_package( Boost 1.55.0 COMPONENTS system regex filesystem atomic chrono thread timer date_time)
endif()

if(Boost_FOUND)
    MESSAGE("BOOST Found!")
else()
    MESSAGE("BOOST not found")
endif()

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_LIBRARY_DIR})	

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
	###set ( CMAKE_CXX_FLAGS "-L/GitRepos/BlockGame/src/External/boost_1_54_0/stage/lib -I/GitRepos/BlockGame/src/External/boost_1_54_0" )
else()
	set( CMAKE_CXX_FLAGS "-std=c++0x -Wno-write-strings -Wl,--no-as-needed -lrt -lX11 -lXxf86vm -lXrandr -lpthread -lXi" ) #-lglfw3
# -L/GitRepos/BlockGame/src/External/boost_1_54_0/stage/lib -I/GitRepos/BlockGame/src/External/boost_1_54_0" )
endif()

add_subdirectory( External )
add_subdirectory( Main )
add_subdirectory( Test )
