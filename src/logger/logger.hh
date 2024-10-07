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
        logger_configuration* p_logger_configuration = nullptr) -> status_code;

    //
    // Logs a message.
    // Expects that the title is valid for the lifetime of the program.
    //
    static
    auto
    log(
        const log_level& p_log_level,
        const char* p_title,
        const std::string&& p_message) -> void;

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
    is_logger_initialized() -> bool;  

    //
    // Initializes the singleton logger instance.
    //
    auto
    initialize(
        const logger_configuration& p_logger_configuration) -> status_code;

    //
    // Logs a message through the singleton logger instance.
    //
    auto
    log(
        const log_level& p_log_level,
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

//
// Log info message macro.
//
#define log_info_message(p_title, p_format, ...) \
    do \
    { \
        assert(logger::is_logger_initialized()); \
        logger::log(log_level::info, p_title, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

//
// Log warning message macro.
//
#define log_warning_message(p_title, p_format, ...) \
    do \
    { \
        assert(logger::is_logger_initialized()); \
        logger::log(log_level::warning, p_title, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

//
// Log error message macro.
//
#define log_error_message(p_title, p_format, ...) \
    do \
    { \
        assert(logger::is_logger_initialized()); \
        logger::log(log_level::error, p_title, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

//
// Log critical message macro.
//
#define log_critical_message(p_title, p_format, ...) \
    do \
    { \
        logger::log(log_level::critical, p_title, std::format(p_format, ##__VA_ARGS__)); \
    } \
    while (false)

} // namespace syp.