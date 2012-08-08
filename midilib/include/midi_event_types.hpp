//
// Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#ifndef MIDI_EVENT_TYPES_HPP
#define MIDI_EVENT_TYPES_HPP

#include <boost/variant.hpp>

/// This namespace contains a struct definition for each type of midi event that can be found in a midi file.
/// The midi file parser will create objects of these types while parsing midi events and add them to a vector for each track in the midi file.
namespace events
{
    /// This type is the base type for note-on, note-off and aftertouch events
    struct note
    {
        unsigned char number;
        unsigned char velocity;
    };

    struct note_off : note
    {};

    struct note_on : note
    {};

    struct note_aftertouch : note
    {};

    struct controller 
    {
        unsigned char which;
        unsigned char value;
    };

    struct program_change
    {
    	explicit program_change( unsigned char program)
    		:program( program){}
    	program_change(){}
        unsigned char program;
    };

    struct channel_aftertouch
    {
    	explicit channel_aftertouch( unsigned char value)
    		:value( value){}
    	channel_aftertouch(){}
        unsigned char value;
    };

    struct pitch_bend
    {
    	explicit pitch_bend( unsigned short value)
    		:value(value){}
    	pitch_bend(){}
        unsigned short value;
    };

    /// All "channel events" (events that have an associated midi channel) are grouped
    /// into this channel_event_variant.
    typedef boost::variant<
        note_on,
        note_off,
        note_aftertouch,
        controller,
        program_change,
        channel_aftertouch,
        pitch_bend> channel_event_variant;

    /// This is not really a midi event, but rather a union of all midi events that have an associated channel number.
    struct channel_event
    {
        unsigned char         channel;
        channel_event_variant event;
    };

    struct meta
    {
        unsigned char       type;
        std::vector<unsigned char>   bytes;
    };

    /// we're not doing anything with sysex messages right now.
    struct sysex
    {
    };

    /// This type can hold any midi event encountered in a midi file.
    typedef boost::variant<
        meta,
        sysex,
        channel_event
    > any;

    /// a timed midi event consists of a time stamp, which holds the time between this event and the previous, followed by a midi event.
    struct timed_midi_event
    {
        unsigned delta_time;
        events::any event;
    };
} // namespace events

#endif // MIDI_EVENT_TYPES_HPP
