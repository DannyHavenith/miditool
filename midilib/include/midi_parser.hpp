//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined( MIDI_PARSER_HPP)
#define MIDI_PARSER_HPP
#include <iosfwd>
#include "midi_file.hpp"

/// parse the midi file represented by stream 'stream' and return the information of that file in output parameter 'result'.
/// This function returns true iff the file could be completely parsed as a midi file.
bool parse_midifile( std::istream &stream, midi_file &result);

#endif //MIDI_PARSER_HPP
