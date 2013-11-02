cmake_minimum_required (VERSION 2.6)

add_subdirectory( Game )
add_subdirectory( Graphics )
add_subdirectory( Utilities )

###set_property( GLOBAL PROPERTY USE_FOLDERS On)

SET_PROPERTY(TARGET Game PROPERTY FOLDER "Main")
SET_PROPERTY(TARGET Utilities PROPERTY FOLDER "Main")
SET_PROPERTY(TARGET Graphics PROPERTY FOLDER "Main")
