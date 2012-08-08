//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

#if !defined( TIMED_MIDI_VISITOR_HPP)
#define TIMED_MIDI_VISITOR_HPP
#include "midi_event_visitor.hpp"
#include "midi_file.hpp"

namespace events
{
    /// This is a specialization of a midi event visitor that keeps track of the current time in seconds.
    /// Derived classes must make sure that this class' meta-event operator() overload is called, because it uses
    /// this event to keep track of tempo changes.
	template<typename Derived>
	struct timed_visitor : public visitor<Derived>
	{
	    /// A timed visitor needs to be constructed with a midi_header, so that it can correctly interpret the time stamp values encountered.
		explicit timed_visitor( const midi_header &h)
			:current_time(0.0), time_step(1.0), ignore_bpm(false), division( h.division)
		{
			if (h.division & 0x8000)
			{
			    // if the msb is set, we interpret the top byte as frames per second (fps) and the
			    // bottom byte as ticks per frame.
				int fps_raw = (h.division & 0x7f00) >> 8;
				double fps = (fps_raw == 29)?29.97:fps_raw;
				time_step = fps * (h.division & 0x00ff);
				ignore_bpm = true;
			}
			else
			{
                // assume 120 bpm (0.5s/beat) at start
				time_step = .5/division;
			}
		}

		using visitor<Derived>::operator();
		using visitor<Derived>::derived;

		/// visit a timed midi event.
		/// This function will adjust the current time based on the delta time in the timed midi event and then call
		/// the derived class' operator() overload for events::any.
		void operator()( const timed_midi_event &event)
		{
			current_time += (event.delta_time * time_step);
			derived()( event.event);
		}

		/// visit a meta event.
		/// If the event is a tempo change. This object will react on that.
        void operator() (const meta &event)
        {
            // react on tempo changes
            if (event.type == 81 && event.bytes.size() == 3 && !ignore_bpm)
            {
                unsigned microseconds_per_quarter_note = (event.bytes[0] << 16) + (event.bytes[1] << 8) + event.bytes[2];
                time_step = (microseconds_per_quarter_note / 1000000.0) / division;
            }
        }

        /// Reset the current time to zero seconds.
		void reset()
		{
			current_time = 0.0;
		}

	protected:
		/// get the time in seconds since the start of the file.
		double get_current_time() const
		{
		    return current_time;
		}

	private:
		double	current_time;
		double  time_step;
		bool	ignore_bpm;
		unsigned int division;
	};


}
#endif //TIMED_MIDI_VISITOR_HPP
