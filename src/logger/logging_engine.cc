// ****************************************************
// Echo Logger C++ Library
// Logger
// 'logging_engine.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include <format>
#include <iostream>
#include "logging_engine.hh"
#include "../utils/uuid_utilities.hh"

namespace echo
{

logging_engine::logging_engine(
    const logger_configuration& p_logger_configuration)
    : m_component_name{p_logger_configuration.component_name},
      m_session_id{uuid_to_string(generate_uuid())},
      m_logging_session_directory_path{
        std::filesystem::absolute(p_logger_configuration.logs_directory_path) /
        std::string(m_component_name + "-logs-" + m_session_id)},
      m_filesystem_writer{m_session_id, m_logging_session_directory_path},
      m_process_id{getpid()},
      m_debug_mode_enabled{p_logger_configuration.debug_mode_enabled},
      m_log_to_syslog_on_failure{p_logger_configuration.log_to_syslog_on_failure},
      m_async_mode_enabled{p_logger_configuration.async_mode_enabled}
{
    //
    // Can throw if the directory creation was not possible.
    //
    std::filesystem::create_directories(m_logging_session_directory_path);
}

auto
logging_engine::log(
    const log_level& p_log_level,
    const std::source_location& p_source_location,
    const char* p_title,
    const char* p_message) -> void
{
    const std::string log_message = create_formatted_log_message(
        p_log_level,
        p_source_location,
        p_title,
        p_message);

    if (m_debug_mode_enabled)
    {
        //
        // Debug mode is enabled. Synchronize the
        // access to the standard output stream.
        // This can become detrimental in highly concurrent scenarios.
        //
        std::scoped_lock<std::mutex> lock {m_std_output_lock};

        log_message_to_console(log_message.c_str());
    }

    if (!m_async_mode_enabled)
    {
        //
        // Sync mode is specified. Write the log
        // message directly to disk and cut the operation.
        // Performance of async mode logging is much greater.
        // Consider switching to async mode for production workloads.
        //
        m_filesystem_writer.write_log_message_to_disk(log_message.c_str());

        return;
    }


}

auto
logging_engine::create_formatted_log_message(
    const log_level& p_log_level,
    const std::source_location& p_source_location,
    const char* p_title,
    const char* p_message) -> std::string
{
    const char* level = nullptr;

    switch (static_cast<std::uint8_t>(p_log_level))
    {
        case static_cast<std::uint8_t>(log_level::info):
        {
            level = c_info_log_level;

            break;
        }
        case static_cast<std::uint8_t>(log_level::warning):
        {
            level = c_warning_log_level;

            break;
        }
        case static_cast<std::uint8_t>(log_level::error):
        {
            level = c_error_log_level;

            break;
        }
        case static_cast<std::uint8_t>(log_level::critical):
        {
            level = c_critical_log_level;

            break;
        }
        default:
        {
            level = c_default_log_level;

            break;
        }
    }

    return std::format(
        "[{}] ({}) PID={}, TID={}, ActivityID={}, File={}, Function={}, Line={}. <{}> [{}] {}\n",
        "Now", // Update.
        m_session_id.c_str(),
        m_process_id,
        syscall(SYS_gettid),
        "123", // Update.
        p_source_location.file_name(),
        p_source_location.function_name(),
        p_source_location.line(),
        level,
        p_title,
        p_message);
}

} // namespace echo.