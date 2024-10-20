// ****************************************************
// Echo Logger C++ Library
// Logger
// 'logger_configuration.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <cstdint>
#include <filesystem>

namespace echo
{

//
// Logger configuration container for specifying logger startup options.
//
struct logger_configuration
{

    //
    // Constructor.
    //
    logger_configuration()
        : debug_mode_enabled{true},
          log_to_syslog_on_failure{true},
          logs_directory_path{std::filesystem::current_path()},
          async_mode_enabled{false},
          utc_enabled{true},
          component_name{"EchoLogger"},
          flush_frequency_ms{1'000},
          include_source_location{true}
    {}

    //
    // Flag for determining whether debug mode is enabled for the logger instance.
    // This will produce console output for debugging purposes. Because of practical
    // synchronization requirements for the standard output stream, exclusive locking is
    // introduced for this option, which can cause contention in highly concurrent scenarios.
    // Limit its use strictly for debugging situations.  
    //
    bool debug_mode_enabled;

    //
    // Flag for determining if logs should be flushed to syslog in case of failure.
    //
    bool log_to_syslog_on_failure;

    //
    // Flag for determining if the loggger will work on sync or async mode.
    //
    bool async_mode_enabled;

    //
    // Flag for determining if the loggger will use UTC or local time for logs.
    //
    bool utc_enabled;

    //
    // Path to the directory where the logging session directory will be created.
    //
    std::filesystem::path logs_directory_path;

    //
    // Component name to be used by the logger for service identification.
    //
    std::string component_name;

    //
    // Disk flush frequency in milliseconds. Only applies for async mode logging.
    //
    std::uint32_t flush_frequency_ms;

    //
    // Flag for determining if source location details should be included in the log message.
    //
    bool include_source_location;

};

} // namespace echo.