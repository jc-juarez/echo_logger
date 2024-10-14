// ****************************************************
// Synapse C++ Library
// Logger
// 'log_message.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <cstdint>
#include <unistd.h>
#include "log_level.hh"
#include <sys/syscall.h>
#include "../uuid/uuid_utilities.hh"

namespace syp
{

struct log_message
{

public:

    log_message(
        const std::string&& p_timestamp,
        const std::string&& p_activity_id,
        const log_level& p_log_level,
        const std::string&& p_message,
        const std::string&& p_file_name,
        const std::string&& p_function_name,
        const std::uint32_t p_line_number,
        const std::string&& p_title)
        : m_timestamp{p_timestamp},
          m_thread_id{syscall(SYS_gettid)},
          m_activity_id{p_activity_id},
          m_message{p_message},
          m_file_name{p_file_name},
          m_function_name{p_function_name},
          m_line_number{p_line_number},
          m_title{p_title}
    {
        switch (static_cast<std::uint8_t>(p_log_level))
        {
            case static_cast<std::uint8_t>(log_level::info):
            {
                m_log_level = c_info_log_level;

                break;
            }
            case static_cast<std::uint8_t>(log_level::warning):
            {
                m_log_level = c_warning_log_level;

                break;
            }
            case static_cast<std::uint8_t>(log_level::error):
            {
                m_log_level = c_error_log_level;

                break;
            }
            case static_cast<std::uint8_t>(log_level::critical):
            {
                m_log_level = c_critical_log_level;

                break;
            }
            default:
            {
                m_log_level = c_default_log_level;

                break;
            }
        }
    }

private:

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
    // Timestamp for when the log was emitted.
    //
    const std::string m_timestamp;

    //
    // Thread ID of the caller.
    //
    const pid_t m_thread_id;

    //
    // Activity ID of the caller.
    //
    const std::string m_activity_id;

    //
    // Log level in its text representation.
    // Points to a data segment allocated memory buffer.
    //
    const char* m_log_level;

    //
    // Log message.
    //
    const std::string m_message;

    //
    // File name.
    //
    const std::string m_file_name;

    //
    // Function name.
    //
    const std::string m_function_name;

    //
    // Line number.
    //
    const std::uint32_t m_line_number;

    //
    // Log title.
    //
    const std::string m_title;

};

} // namespace syp.