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

file(GLOB LAUNCHPADSRC
    "*.h"
    "*.cpp"
	"state/*.h"
	"stage/*.h"
	"stage/*.cpp"
	"stage/teststages/*.h"
	"stage/teststages/*.cpp"
	"transition/*.h"
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

add_executable(Launchpad ${LAUNCHPADSRC} )

target_link_libraries(Launchpad
		Game
		Graphics
		Utilities
)

#message(STATUS "Target File Dir :: " $<TARGET_FILE_DIR:Launchpad>)

ADD_CUSTOM_COMMAND(TARGET Launchpad
          POST_BUILD
          COMMAND ${CMAKE_COMMAND} -E make_directory $<TARGET_FILE_DIR:Launchpad>/Resources
          COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_SOURCE_DIR}/Main/Resources $<TARGET_FILE_DIR:Launchpad>/Resources
)
