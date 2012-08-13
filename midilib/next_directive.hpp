//
//  Copyright (C) 2012 Danny Havenith
//
//  Distributed under the Boost Software License, Version 1.0. (See
//  accompanying file LICENSE_1_0.txt or copy at
//  http://www.boost.org/LICENSE_1_0.txt)
//

// Subrange parser
// This file defines a spirit (2.x) directive that limits a parser to parse only a given number of input tokens
//

#ifndef SUBRANGE_PARSER_HPP_INCLUDED
#define SUBRANGE_PARSER_HPP_INCLUDED

#include <boost/spirit/home/support/info.hpp>
#include <boost/spirit/home/qi/meta_compiler.hpp>
#include <boost/spirit/home/qi/parser.hpp>
#include <boost/spirit/home/qi/auxiliary/lazy.hpp>
#include <boost/spirit/home/support/attributes.hpp>
#include <boost/fusion/include/at.hpp>
#include <boost/fusion/container/vector.hpp>

#include <iterator> // for std::advance


namespace subrange_directive
{
    BOOST_SPIRIT_TERMINAL_EX( subrange)
}
using subrange_directive::subrange;

// plug our parser into the spirit metagrammar.
namespace boost { namespace spirit 
{
    
    // enable subrange(size)[p]
    template< typename T>
    struct use_directive<
        qi::domain,
        terminal_ex< 
            subrange_directive::tag::subrange,
            fusion::vector1<T>
        >
    > : mpl::true_ {};

    // enable *lazy* subrange(size)[p]
    template <>                                     
    struct use_lazy_directive<
        qi::domain,
        subrange_directive::tag::subrange,
        1 // arity
    > : mpl::true_ {};

}} // end namespace boost::spirit

namespace subrange_directive
{

    using namespace ::boost::spirit::qi;


    /// Subrange parser.
    /// This parser (directive) is used to limit a parser p to only the next n input tokens
    /// Usage is like this: subrange(n)[p]
    /// An example of its use is in a--binary--midi chunk parser where it would be used like this:
    ///    subrange(chunk_size)[*midi_event]
    /// in this particular case this would parse the next 'chunk_size' bytes as a sequence of midi_events
    template< typename Subject>
    struct subrange_parser
        :unary_parser< subrange_parser<Subject> >
    {
        /// subject_type is the type of the parser we're enclosing
        typedef Subject subject_type;

        /// The attribute of this parser is the attribute of the enclosed parser.
        template <typename Context, typename Iterator>
        struct attribute
        {

            typedef typename
                boost::spirit::traits::attribute_of< subject_type, Context, Iterator>::type
                    type;
        };

        subrange_parser( Subject const &sub, ptrdiff_t off)
            : subject( sub), offset(off) {};

        template <
            typename Iterator, typename Context
          , typename Skipper, typename Attribute>
        bool parse(
            Iterator& first, Iterator const& last
          , Context& context, Skipper const& skipper
          , Attribute& attr) const
        {
            // limit parsing to the range (first,first+arg1>

            // first check if we have arg1 tokens left
            if (std::distance( first, last) < offset)
            {
                return false;
            }
            else
            {
                Iterator local_end = first;
                std::advance( local_end, offset);

                return subject.parse(
                    first,  local_end,
                    context, skipper, attr);
            }
        }

        template <typename Context>
        info what(Context const& ctx)
        {
            return info( "subrange", subject.what( ctx));
        }

        Subject           subject;
        const ptrdiff_t   offset;
    };
}


namespace boost { namespace spirit { 
    namespace qi {


        template< typename T, typename Subject, typename Modifiers>
        struct make_directive<
                terminal_ex<
                        subrange_directive::tag::subrange, 
                        fusion::vector1<T> 
                    >,
                Subject, Modifiers
                >
        {
            typedef subrange_directive::subrange_parser< Subject> result_type;
            template< typename Terminal>
            result_type operator()(
                Terminal const &term, Subject const &subject, unused_type) const
            {
                return result_type( subject, fusion::at_c<0>( term.args));
            }
        };
    }

    namespace traits {
    	/// A subrange parser has a semantic action if the enclosed parser has one.
        template< typename Subject>
        struct has_semantic_action< subrange_directive::subrange_parser< Subject> >
            : unary_has_semantic_action< Subject> {};

        template< typename Subject, typename Attribute, typename Context, typename Iterator>
        struct handles_container<
            subrange_directive::subrange_parser< Subject>,
            Attribute, Context, Iterator
                    >
            :unary_handles_container< Subject, Attribute, Context, Iterator> {};

    }

}}
#endif // SUBRANGE_PARSER_HPP_INCLUDED
