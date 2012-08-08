//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

/// This file adapts the midi-file specific structs of midi_file.hpp to become first-class fusion tuple types.

#ifndef MIDI_FILE_FUSION_HPP
#define MIDI_FILE_FUSION_HPP
#include "midi_events_fusion.hpp"
#include "include/midi_file.hpp"
#include <boost/fusion/include/adapt_struct.hpp>

BOOST_FUSION_ADAPT_STRUCT(
    midi_header,
    (unsigned, format)
    (unsigned, number_of_tracks)
    (unsigned, division)
 )

BOOST_FUSION_ADAPT_STRUCT(
    midi_file,
    (midi_header, header)
    (std::vector<midi_track>, tracks)
)


#endif //MIDI_FILE_FUSION_HPP
