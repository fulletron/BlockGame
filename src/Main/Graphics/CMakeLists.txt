cmake_minimum_required (VERSION 2.6)

file(GLOB GRAPHICSSRC
    "*.h"
    "*.cpp"
    "buildres/*.cpp"
	"panes/*.h"
	"panes/*.cpp"
)

macro(GroupSources curdir)
	file(GLOB children RELATIVE ${PROJECT_SOURCE_DIR}/${curdir}
	${PROJECT_SOURCE_DIR}/${curdir}/*)
	foreach(child ${children})
		if(IS_DIRECTORY ${PROJECT_SOURCE_DIR}/${curdir}/${child})
			GroupSources(${curdir}/${child})
		else()
			string(REPLACE "/" "\\" groupname ${curdir})
                  		string(REPLACE "src" "Common" groupname ${groupname})
             			source_group(${groupname} FILES
 			${PROJECT_SOURCE_DIR}/${curdir}/${child})
		endif()
   	endforeach()
endmacro()

#SOURCE_GROUP(buildres FILES "buildres/*.cpp")
#SOURCE_GROUP(panes FILES "panes/*.cpp" "panes/*h")


add_library( Graphics ${GRAPHICSSRC} )
target_link_libraries( Graphics
		Utilities
)

add_library( GraphicsTest ${GRAPHICSSRC} )
target_link_libraries( GraphicsTest
		UtilitiesTest
)

SET_TARGET_PROPERTIES(GraphicsTest PROPERTIES
        COMPILE_DEFINITIONS "TEST_ENABLED;") 
SET_PROPERTY(TARGET GraphicsTest PROPERTY FOLDER "Test/Mirror")
