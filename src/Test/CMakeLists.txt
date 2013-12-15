cmake_minimum_required (VERSION 2.6)

add_subdirectory( UtilitiesTester )
add_subdirectory( GraphicsTester )

SET_PROPERTY( TARGET UtilitiesTester PROPERTY FOLDER "Test" )
SET_PROPERTY( TARGET GraphicsTester PROPERTY FOLDER "Test" )