// ****************************************************
// Echo Logger C++ Library
// Logger
// 'logger.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include <mutex>
#include <string>
#include <iostream>
#include <syslog.h>
#include "logger.hh"
#include "logging_engine.hh"

namespace echo
{

auto
logger::is_logger_initialized() -> bool
{
    return get_logger().is_logger_initialized_implementation();
}

auto
logger::initialize(
    logger_configuration* p_logger_configuration) -> void
{
    logger_configuration default_logger_configuration;

    if (p_logger_configuration == nullptr)
    {
        //
        // No custom configuration was provided; use the default settings.
        //
        p_logger_configuration = &default_logger_configuration;
    }

    get_logger().initialize_implementation(
        *p_logger_configuration);
}

auto
logger::flush() -> void
{
    // Pending implementation.
}

logger::logger()
    : m_logging_engine{nullptr}
{}

auto
logger::is_logger_initialized_implementation() -> bool
{
    std::shared_lock lock {m_lock};

    return m_logging_engine != nullptr;
}  

auto
logger::initialize_implementation(
    const logger_configuration& p_logger_configuration) -> void
{
    std::unique_lock lock {m_lock};

    if (m_logging_engine != nullptr)
    {
        //
        // The logging engine has already been initialized; nothing to do here.
        //
        throw std::logic_error("The echo logger has already been initialized.");
    }

    m_logging_engine = std::make_unique<logging_engine>(
        p_logger_configuration);
}

auto
logger::log_implementation(
    const log_level& p_log_level,
    const std::source_location& p_source_location,
    const char* p_title,
    const char* p_message) -> void
{
    std::shared_lock lock {m_lock};

    if (m_logging_engine == nullptr)
    {
        //
        // The logging engine is not yet initialized; nothing to do here.
        //
        throw std::logic_error("The echo logger is not yet initialized.");
    }

    m_logging_engine->log(
        p_log_level,
        p_source_location,
        p_title,
        p_message);
}

auto
logger::get_logger() -> logger&
{
    static logger singleton_logger_instance;

    return singleton_logger_instance;
}

auto
logger::log_error_fallback(
    const char* p_title,
    const char* p_message) -> void
{
    const std::string formatted_message = "<!> Error: " + std::string(p_message) + "\n";
    log_error_to_syslog(p_title, formatted_message.c_str());
    log_error_to_console(formatted_message.c_str());
}

auto
logger::log_error_to_console(
    const char* p_message) -> void
{
    std::cerr << p_message;
}

auto
logger::log_error_to_syslog(
    const char* p_title,
    const char* p_message) -> void
{
    openlog(p_title, LOG_PID | LOG_CONS, LOG_USER);
    syslog(LOG_ERR, "%s", p_message);
    closelog();
}

} // namespace echo.