// ****************************************************
// Echo Logger C++ Library
// Logger
// 'logging_engine.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <mutex>
#include <unistd.h>
#include "log_level.hh"
#include <source_location>
#include "../status/status.hh"
#include "filesystem_writer.hh"
#include "logger_configuration.hh"

namespace echo
{

//
// Logging engine used for logs memory placement and filesystem flushing.
//
class logging_engine
{

public:

    logging_engine(
        const logger_configuration& p_logger_configuration);

    auto
    initialize(
        const char* p_component_name,
        const logger_configuration& p_logger_configuration) -> status_code;

    auto
    log(
        const log_level& p_log_level,
        const std::source_location& p_source_location,
        const char* p_title,
        const char* p_message) -> void;

private:

    //
    // Constructs the log message with formatting.
    //
    auto
    create_formatted_log_message(
        const log_level& p_log_level,
        const std::source_location& p_source_location,
        const char* p_title,
        const char* p_message) -> std::string;

    inline
    static
    auto
    log_message_to_console(
        const char* p_message) -> void
    {
        std::cout << p_message << "\n";
    }

    inline
    static
    auto
    log_error_to_console(
        const char* p_message) -> void
    {
        std::cerr << p_message << "\n";
    }

    //
    // Text representation for info level logs.
    //
    static constexpr const char* c_info_log_level = "Info";

    //
    // Text representation for warning level logs.
    //
    static constexpr const char* c_warning_log_level = "Warning";

    //
    // Text representation for error level logs.
    //
    static constexpr const char* c_error_log_level = "Error";

    //
    // Text representation for critical level logs.
    //
    static constexpr const char* c_critical_log_level = "Critical";

    //
    // Text representation for default level logs.
    //
    static constexpr const char* c_default_log_level = "Unknown";

    //
    // Flag for determining whether debug mode is enabled for the logger instance.
    //
    const bool m_debug_mode_enabled;

    //
    // Flag for determining if logs should be flushed to syslog in case of failure.
    //
    const bool m_log_to_syslog_on_failure;

    //
    // Component name.
    //
    const std::string m_component_name;

    //
    // Flag for determining if the loggger will work on sync or async mode.
    //
    const bool m_async_mode_enabled;

    //
    // Logging session identifier.
    //
    const std::string m_session_id;

    //
    // Path to the directory where the logs for the logging session will be stored.
    //
    const std::filesystem::path m_logging_session_directory_path;

    //
    // Process ID for the logging session.
    //
    const pid_t m_process_id;

    //
    // Lock for synchronizing access to the standard output stream.
    // Only used when debug mode is enabled.
    //
    std::mutex m_std_output_lock;

    //
    // Filesystem writer class for handling log writes to disk.
    //
    filesystem_writer m_filesystem_writer;

};

} // namespace echo.