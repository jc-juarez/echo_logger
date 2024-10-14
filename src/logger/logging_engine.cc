// ****************************************************
// Synapse C++ Library
// Logger
// 'logging_engine.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include <iostream> // remove.
#include <format>
#include "log_message.hh"
#include "logging_engine.hh"
#include "../uuid/uuid_utilities.hh"

namespace syp
{

logging_engine::logging_engine()
    : m_process_id(getpid()),
      m_session_id(uuid_to_string(generate_uuid()))
{}

auto
logging_engine::initialize(
    const char* p_component_name,
    const logger_configuration& p_logger_configuration) -> status_code
{
    m_component_name = p_component_name;
    m_debug_mode_enabled = p_logger_configuration.m_debug_mode_enabled;
    m_log_to_syslog_on_failure = p_logger_configuration.m_log_to_syslog_on_failure;
    const std::filesystem::path logs_directory_path = std::filesystem::absolute(p_logger_configuration.m_logs_directory_path);
    
    //
    // Define the path to the directory where the actual logs will be stored.
    //
    m_logging_session_directory_path = logs_directory_path;
    m_logging_session_directory_path.append(m_component_name + "-logs-" + m_session_id);
    
    try
    {
        std::filesystem::create_directories(m_logging_session_directory_path);
    }
    catch (const std::filesystem::filesystem_error& exception)
    {
        return status::directory_creation_failed;
    }
    
    return status::success;
}

auto
logging_engine::log(
    const log_level& p_log_level,
    const std::source_location& p_source_location,
    const char* p_title,
    const char* p_message) -> void
{
    const char* level = nullptr;

    switch (static_cast<std::uint8_t>(p_log_level))
    {
        case static_cast<std::uint8_t>(log_level::info):
        {
            level = "Info";

            break;
        }
        case static_cast<std::uint8_t>(log_level::warning):
        {
            level = "Warning";

            break;
        }
        case static_cast<std::uint8_t>(log_level::error):
        {
            level = "Error";

            break;
        }
        case static_cast<std::uint8_t>(log_level::critical):
        {
            level = "Critical";

            break;
        }
        default:
        {
            level = "Unknown";

            break;
        }
    }

    const std::string formatted_message = std::format(
        "[{}] ({}) PID={}, TID={}, ActivityID={}, File={}, Function={}, Line={}. <{}> [{}] {}\n",
        "Now",
        m_session_id.c_str(),
        m_process_id,
        syscall(SYS_gettid),
        "123",
        p_source_location.file_name(),
        p_source_location.function_name(),
        p_source_location.line(),
        level,
        p_title,
        p_message);

    std::cout << formatted_message << std::endl;
}

} // namespace syp.