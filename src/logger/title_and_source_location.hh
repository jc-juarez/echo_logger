// ****************************************************
// Synapse C++ Library
// Logger
// 'title_and_source_location.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <format>
#include <source_location>

namespace syp
{

//
// Container for storing the title of a log message and
// the source location information from its call place.
//
struct title_and_source_location
{
    
    //
    // Converting constructor for implicit conversion from arguments.
    //
    title_and_source_location(
        const char* p_title,
        const std::source_location p_source_location = std::source_location::current())
        : m_title{p_title},
          m_source_location{p_source_location}
    {}

    //
    // Title of the log message.
    //
    const char* m_title;

    //
    // Source location for the call place of a log message.
    //
    const std::source_location m_source_location;

};

} // namespace syp.