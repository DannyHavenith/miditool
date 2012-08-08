//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined(MIDI_EVENT_VISITOR_HPP)
#define MIDI_EVENT_VISITOR_HPP

#include <boost/variant/apply_visitor.hpp>
#include "midi_event_types.hpp"

namespace events
{

    /// A base class for midi event visitors.
    /// This class has empty default implementations for most operator()-overloads.
    /// A few implementations are non-trivial though:
    ///  * in a timed_midi_event, the timestamp is ignored and the actual event is visited
    ///  * when an 'any' semi-event is encountered, the actual, typed midi event will be visited
    ///  * when a channel-event semi-event is encountered, the actual  typed midi event will be visited after taking note
    ///    of the channel that was mentioned in that event.
	template<typename Derived>
	struct visitor : public boost::static_visitor<>
	{
		Derived &derived()
		{
			return *static_cast<Derived*>(this);
		}

		const Derived &derived() const
		{
			return *static_cast<Derived*>(this);
		}

		/// ignore the time stamp and descent into the actual event.
        void operator()( const timed_midi_event &event)
        {
            derived()( event.event);
        }

        /// figure out the actual type of the event and visit that one.
        void operator()( const any &event)
		{
			boost::apply_visitor( derived(), event);
		}

        /// figure out the actual type of the channel event and visit that one.
        /// the channel number is stored before visiting the typed event.
		void operator()( const channel_event &event)
		{
			current_channel = event.channel;
			boost::apply_visitor( derived(), event.event);
		}

		void operator()( const meta &)
		{
		}

		void operator()( const sysex &)
		{
		}


		void operator()( const note_on &){}
		void operator()( const note_off &){}
		void operator()( const note_aftertouch &){}
		void operator()( const controller &){}
		void operator()( const program_change &){}
		void operator()( const channel_aftertouch &){}
		void operator()( const pitch_bend &){}

		unsigned short current_channel;
	};

	template<typename Derived>
	struct simple_timed_visitor : public visitor<Derived>
	{
		simple_timed_visitor()
			:current_time(0)
		{

		}

		using events::visitor<Derived>::operator();
		using events::visitor<Derived>::derived;

		void operator()( const timed_midi_event &event)
		{
			current_time += event.delta_time;
			derived()( event.event);
		}

		void reset()
		{
			current_time = 0;
		}

		size_t current_time;
	};

} // namespace events


#endif //MIDI_EVENT_VISITOR_HPP
