// ****************************************************
// Synapse C++ Library
// Logger
// 'logger.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <mutex>
#include <string>
#include <iostream>
#include <syslog.h>
#include "logger.hh"
#include "logging_engine.hh"

namespace syp
{

auto
logger::is_logger_initialized() -> bool
{
    return get_logger().is_logger_initialized();
}

auto
logger::initialize(
    logger_configuration* p_logger_configuration) -> status_code
{
    logger_configuration default_logger_configuration;

    if (p_logger_configuration == nullptr)
    {
        //
        // No custom configuration was provided; use the default settings.
        //
        p_logger_configuration = &default_logger_configuration;
    }

    return get_logger().initialize(*p_logger_configuration);
}

auto
logger::log(
    const log_level& p_log_level,
    const char* p_title,
    const std::string&& p_message) -> void
{
    get_logger().log(
        p_log_level,
        p_title,
        p_message.c_str());
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
logger::is_logger_initialized() -> bool
{
    std::shared_lock lock {m_lock};

    return m_logging_engine != nullptr;
}  

auto
logger::initialize(
    const logger_configuration& p_logger_configuration) -> status_code
{
    std::unique_lock lock {m_lock};

    if (m_logging_engine != nullptr)
    {
        //
        // The logging engine has already been initialized; nothing to do here.
        //
        log_error_fallback("SynapseLogger",
            "The synapse logger has already been initialized.");

        return status::logger_already_initialized;
    }

    std::unique_ptr<logging_engine> current_logging_engine = std::make_unique<logging_engine>();

    status_code status {current_logging_engine->initialize(p_logger_configuration)};

    if (status::failed(status))
    {
        //
        // Initialization failed; do not update the internal logging engine.
        //
        log_error_fallback("SynapseLogger",
            "The synapse logger encountered an error during the initialization process.");

        return status;
    }

    m_logging_engine = std::move(current_logging_engine);
}

auto
logger::log(
    const log_level& p_log_level,
    const char* p_title,
    const char* p_message) -> void
{
    std::shared_lock lock {m_lock};

    if (m_logging_engine == nullptr)
    {
        //
        // The logging engine is not yet initialized; nothing to do here.
        //
        log_error_fallback("SynapseLogger",
            "The synapse logger is not yet initialized.");

        return;
    }

    m_logging_engine->log(
        p_log_level,
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

} // namespace syp.