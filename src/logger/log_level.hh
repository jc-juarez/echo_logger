// ****************************************************
// Synapse C++ Library
// Logger
// 'log_level.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <cstdint>

namespace syp
{

//
// Log level for logs classification.
//
enum class log_level : std::uint8_t
{

    //
    // Information level logs.
    // Used for debugging actions occurring in the system.
    //
    info = 0,

    //
    // Warning level logs.
    // Used for non-error-related events that require attention.
    //
    warning = 1,

    //
    // Error level logs.
    // Used for error-related events that indicate a failed action.
    //
    error = 2,

    //
    // Critical level logs.
    // Used for critical error-related events that may provoke a system shutdown.
    //
    critical = 3
    
};

} // namespace syp.