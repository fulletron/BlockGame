cmake_minimum_required (VERSION 2.6)

file(GLOB GTESTSRC
    "*.h"
    "*.cpp"
)

add_library(GTEST ${GTESTSRC} )

SET_PROPERTY(TARGET GTEST                    PROPERTY FOLDER "External/GTEST")