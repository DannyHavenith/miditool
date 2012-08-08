##          Copyright Danny Havenith 2012.
## Distributed under the Boost Software License, Version 1.0.
##    (See accompanying file LICENSE_1_0.txt or copy at
##          http://www.boost.org/LICENSE_1_0.txt)

## This is the cmake file for the miditool executable.
## This executable uses midilib and uses it to demonstrate how visitors can be used to 
## perform simple operations on midi files.

add_executable( 
	miditool
	
	miditool.cpp
	)

TARGET_LINK_LIBRARIES( miditool midilib)
