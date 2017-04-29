cmake_minimum_required (VERSION 2.6)

#turn this into a macro
# file(GLOB GRAPHICSSRC
    # "*.h"
    # "*.cpp"
    # "BuildRes/*.cpp"
    # "Panes/DebugPane/*.h"
    # "Panes/DebugPane/*.cpp"
# )

file(GLOB GRAPHICSSRC
    "*.h"
    "*.cpp"
	"window/*.h"
	"window/*.cpp"
	"library/*.h"
	"library/*.cpp"
	"resource/*.h"
	"resource/*.cpp"
)

#message( "CALLING GROUPSOURCES on" ${CMAKE_CURRENT_SOURCE_DIR}  )
GroupSources( ${CMAKE_CURRENT_SOURCE_DIR} "GENERAL" )

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
