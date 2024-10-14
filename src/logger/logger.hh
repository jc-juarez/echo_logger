// ****************************************************
// Synapse C++ Library
// Logger
// 'logger.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <format>
#include <memory>
#include <cassert>
#include <shared_mutex>
#include "log_level.hh"
#include "../status/status.hh"
#include "logger_configuration.hh"
#include "title_and_source_location.hh"

namespace syp
{

class logging_engine;

//
// Logger singleton class for managing logging in the system.
//
class logger
{
    
public:

    //
    // Gets the logger initialization status.
    //
    static
    auto
    is_logger_initialized() -> bool;  

    //
    // Initializes singleton logger instance.
    //
    static
    auto
    initialize(
        const std::string p_component_name = "synapse",
        logger_configuration* p_logger_configuration = nullptr) -> status_code;

    //
    // Logs a message.
    // Expects that the title is valid for the lifetime of the program.
    // Generates a compile-time error on failed format validations.
    //
    template<typename... Args>
    static
    auto
    log(
        const log_level& p_log_level,
        title_and_source_location p_title_and_source_location,
        std::format_string<Args...> p_format,
        Args&&... p_args) -> void
    {
        const std::string formatted_message = std::format(p_format, std::forward<Args>(p_args)...);

        get_logger().log_implementation(
            p_log_level,
            p_title_and_source_location.m_source_location,
            p_title_and_source_location.m_title,
            formatted_message.c_str());
    }

    //
    // Flushes the current contents of the memory buffer to the filesystem.
    //
    static
    auto
    flush() -> void;

private:

    //
    // Constructor for the singleton logger instance.
    //
    logger();

    //
    // Gets the logger initialization status.
    //
    auto
    is_logger_initialized_implementation() -> bool;  

    //
    // Initializes the singleton logger instance.
    //
    auto
    initialize_implementation(
        const char* p_component_name,
        const logger_configuration& p_logger_configuration) -> status_code;

    //
    // Logs a message through the singleton logger instance.
    //
    auto
    log_implementation(
        const log_level& p_log_level,
        const std::source_location& p_source_location,
        const char* p_title,
        const char* p_message) -> void;

    //
    // Gets and constructs the singleton logger instance by lazy initialization.
    //
    static
    auto
    get_logger() -> logger&;

    //
    // Logs a message to the standard error stream and syslog.
    // Not thread-safe; caller responsible for synchronization.
    //
    static
    auto
    log_error_fallback(
        const char* p_title,
        const char* p_message) -> void;

    //
    // Logs a message to the standard error stream.
    // Not thread-safe; caller responsible for synchronization.
    //
    static
    auto
    log_error_to_console(
        const char* p_message) -> void;

    //
    // Logs a message to syslog.
    // Not thread-safe; caller responsible for synchronization.
    //
    static
    auto
    log_error_to_syslog(
        const char* p_title,
        const char* p_message) -> void;

    //
    // Logging engine used to handle logs dispatching.
    //
    std::unique_ptr<logging_engine> m_logging_engine;

    //
    // Lock for handling access synchronization to the object.
    //
    mutable std::shared_mutex m_lock;

};

} // namespace syp.