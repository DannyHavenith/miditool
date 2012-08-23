//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

/// This file adapts the event types of midi_event_types.hpp to become first-class fusion tuples.
/// This allows the structs to become synthesized attributes of spirit rules.

#ifndef MIDI_EVENTS_FUSION_HPP
#define MIDI_EVENTS_FUSION_HPP
#include <boost/fusion/include/adapt_struct.hpp>
#include "include/midi_event_types.hpp"

BOOST_FUSION_ADAPT_STRUCT(
    events::note_on,
    (unsigned char, number)
    (unsigned char, velocity)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::meta,
    (unsigned char, type)
    (std::vector<unsigned char>, bytes)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::note_off,
    (unsigned char, number)
    (unsigned char, velocity)
    )
BOOST_FUSION_ADAPT_STRUCT(
    events::note_aftertouch,
    (unsigned char, number)
    (unsigned char, velocity)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::controller,
    (unsigned char, which)
    (unsigned char, value)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::program_change,
    (unsigned char, program)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::channel_aftertouch,
    (unsigned char, value)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::pitch_bend,
    (unsigned short, value)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::channel_event,
    (unsigned char, channel)
    (events::channel_event_variant, event)
    )

BOOST_FUSION_ADAPT_STRUCT(
    events::timed_midi_event,
    (unsigned, delta_time)
    (events::midi_event, event)
    )

#endif //MIDI_EVENTS_FUSION_HPP
