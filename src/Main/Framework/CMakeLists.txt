cmake_minimum_required (VERSION 2.6)

#file(GLOB GAMESRC
#    "*.h"
#    "*.cpp"
#	"charactercreationstates/*.h"
#	"charactercreationstates/*.cpp"
#	"characterchosenstates/*.h"
#	"characterchosenstates/*.cpp"	
#	"characterchosenstates/menustates/*.h"
#	"characterchosenstates/menustates/*.cpp"
#	"characterchosenstates/directorstates/*.h"
#	"characterchosenstates/directorstates/*.cpp"
#)

file(GLOB FRAMEWORKSRC
    "*.h"
    "*.cpp"
	"state/*.h"
	"stage/*.h"
	"stage/*.cpp"
	"transition/*.h"
	"panel/*.h"
	"panel/*.cpp"
	"actor/*.h"
	"actor/*.cpp"
	"scene/*.h"
	"scene/*.cpp"
	"referencer/*.h"
	"server/*.h"
	"client/*.h"
	"memory/*.h"
)

#set(
#    source_list
#    "*.h"
#    "*.cpp"
#	"charactercreationstates/*.h"
#	"charactercreationstates/*.cpp"
#	"characterchosenstates/*.h"
#	"characterchosenstates/*.cpp"	
#	"characterchosenstates/menustates/*.h"
#	"characterchosenstates/menustates/*.cpp"
#)

#maybe this will help?
GroupSources( ${CMAKE_CURRENT_SOURCE_DIR} "GENERAL" )	

##add_executable(Launchpad ${LAUNCHPADSRC} )
add_library( Framework STATIC ${FRAMEWORKSRC} )

target_link_libraries(Framework
		Game
		Graphics
		Utilities
)

#message(STATUS "Target File Dir :: " $<TARGET_FILE_DIR:Launchpad>)

#ADD_CUSTOM_COMMAND(TARGET Framework
#          POST_BUILD
#          COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Launchpad>/Resources
#          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Main/Resources $<TARGET_FILE_DIR:Framework>/Resources
#)
