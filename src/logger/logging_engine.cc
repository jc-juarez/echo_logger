// ****************************************************
// Synapse C++ Library
// Logger
// 'logging_engine.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include "logging_engine.hh"
#include <iostream> // remove.

namespace syp
{

logging_engine::logging_engine()
{}

auto
logging_engine::initialize(
    const logger_configuration& p_logger_configuration) -> status_code
{
    return status::success;
}

auto
logging_engine::log(
    const log_level& p_log_level,
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
            level = "Warn";

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

    std::cout << level << " - " << p_title << " - " << p_message << std::endl;
}

} // namespace syp.