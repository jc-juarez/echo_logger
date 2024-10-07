// ****************************************************
// Synapse C++ Library
// Logger
// 'logger_configuration.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <filesystem>

namespace syp
{

//
// Logger configuration container for storing logger startup options.
//
struct logger_configuration
{

    //
    // Constructor.
    //
    logger_configuration()
        : m_debug_mode_enabled{c_default_debug_mode_enabled},
          m_log_to_syslog_on_failure{c_default_log_to_syslog_on_failure},
          m_logs_directory_path{std::filesystem::current_path()}
    {}

    //
    // Flag for determining whether debug mode is enabled for the logger instance.
    //
    bool m_debug_mode_enabled;

    //
    // Flag for determining if logs should be flushed to syslog in case of failure.
    //
    bool m_log_to_syslog_on_failure;

    //
    // Path to the directory for storing logs files.
    //
    std::filesystem::path m_logs_directory_path;

    //
    // Default log to syslog on failure value.
    //
    static constexpr bool c_default_log_to_syslog_on_failure = true;

    //
    // Default debug mode enabled value.
    //
    static constexpr bool c_default_debug_mode_enabled = true;

};

} // namespace syp.