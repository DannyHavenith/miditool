//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

/// This file contains the definition of a few types that represent data that can be found in midi files.

#if !defined(MIDI_FILE_HPP)
#define MIDI_FILE_HPP

#include <vector>
#include "midi_event_types.hpp"

/// typedef for a chronologically ordered container of timed midi events.
typedef std::vector< events::timed_midi_event>   midi_track;

/// Information of a midi file header chunk.
struct midi_header
{
    unsigned format;
    unsigned number_of_tracks;
    unsigned division;
};

/// In-memory representation of the information found in a midi file.
struct midi_file
{
	typedef std::vector<midi_track> tracks_type;
    midi_header header;
    tracks_type tracks;
};

#endif //MIDI_FILE_HPP
