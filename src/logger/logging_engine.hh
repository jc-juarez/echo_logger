// ****************************************************
// Synapse C++ Library
// Logger
// 'logging_engine.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <unistd.h>
#include "log_level.hh"
#include <source_location>
#include "../status/status.hh"
#include "logger_configuration.hh"

namespace syp
{

//
// Logging engine used for logs memory placement and filesystem flushing.
//
class logging_engine
{

public:

    logging_engine();

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
    // Flag for determining whether debug mode is enabled for the logger instance.
    //
    bool m_debug_mode_enabled;

    //
    // Flag for determining if logs should be flushed to syslog in case of failure.
    //
    bool m_log_to_syslog_on_failure;

    //
    // Component name.
    //
    std::string m_component_name;

    //
    // Logging session identifier.
    //
    const std::string m_session_id;

    //
    // Path to the directory where the logs for the logging session will be stored.
    //
    std::filesystem::path m_logging_session_directory_path;

    //
    // Process ID for the logging session.
    //
    const pid_t m_process_id;

};

} // namespace syp.