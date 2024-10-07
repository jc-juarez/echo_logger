// ****************************************************
// Synapse C++ Library
// Logger
// 'logger.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include "logger.hh"

namespace syp
{

std::atomic<bool> logger::s_initialized = false;

auto
logger::initialize(
    logger_configuration* p_logger_configuration) -> status_code
{
    if (s_initialized)
    {
        log_critical_message("SynapseLogger",
            "The synapse logger has already been initialized.");

        return status::logger_already_initialized;
    }

    logger_configuration default_logger_configuration;

    if (p_logger_configuration == nullptr)
    {
        //
        // No custom configuration was provided; use the default values.
        //
        p_logger_configuration = &default_logger_configuration;
    }

    status_code status {status::success};

    //
    // In the initialize path, the logger
    // configuration should never be nullptr.
    //
    log(log_level::info,
        "SynapseLogger",
        "The synapse logger has been successfully initialized.",
        &status,
        p_logger_configuration);

    return status;
}

auto
logger::log(
    const log_level& p_log_level,
    const char* p_title,
    const std::string&& p_message,
    status_code* p_status = nullptr,
    const logger_configuration* p_logger_configuration) -> void
{
    if (!s_initialized &&
        p_logger_configuration == nullptr)
    {
        //
        // Log error using fallback mechanism.
        // Thread-safety not guaranteed at this point.
        //
        // log_error_fallback();

        *p_status = status::logger_not_initialized;
        return;
    }

    static logger logger_singleton_instance;

    if (!s_initialized)
    {
        status_code status = logger_singleton_instance.initialize(p_logger_configuration);

        if (status::failed(status))
        {
            //
            // Log error using fallback mechanism.
            // Thread-safety not guaranteed at this point.
            //
            // log_error_fallback();

            *p_status = status;
            return;
        }
    }

    //
    // Set the fact that the logger has now been initialized.
    //
    s_initialized = true;
}

auto
logger::flush() -> void
{

}

auto
logger::is_logger_initialized() -> bool
{

}  

logger::logger()
{

}

auto
logger::initialize(
    const logger_configuration* p_logger_configuration) -> status_code
{

}

} // namespace syp.