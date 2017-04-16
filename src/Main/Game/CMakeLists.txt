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

file(GLOB GAMESRC
    "*.h"
    "*.cpp"
	"state/*.h"
	"overstate/*.h"
	"overstate/*.cpp"
	"overstate/teststates/*.h"
	"overstate/teststates/*.cpp"
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
