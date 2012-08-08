##          Copyright Danny Havenith 2012.
## Distributed under the Boost Software License, Version 1.0.
##    (See accompanying file LICENSE_1_0.txt or copy at
##          http://www.boost.org/LICENSE_1_0.txt)

## This is the main CMakeLists file for the miditool project.


cmake_minimum_required(VERSION 2.6)

project(miditool)
add_definitions(-D_SCL_SECURE_NO_WARNINGS)

SET(Boost_USE_STATIC_LIBS OFF)
SET(Boost_USE_MULTITHREAD ON)
FIND_PACKAGE( Boost)

include_directories( ${miditool_SOURCE_DIR})
add_subdirectory (miditool)
add_subdirectory (midilib)
