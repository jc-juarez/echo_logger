// ****************************************************
// Synapse C++ Library
// Logger
// 'logger.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <atomic>
#include <format>
#include <cassert>
#include "log_level.hh"
#include "logging_engine.hh"
#include "../status/status.hh"
#include "logger_configuration.hh"

namespace syp
{

//
// Logger singleton class for managing logging in the system.
//
class logger
{
    
public:

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
        const std::string&& p_message,
        status_code* p_status = nullptr,
        const logger_configuration* p_logger_configuration = nullptr) -> void;

    //
    // Flushes the current contents of the memory buffer to the filesystem.
    //
    static
    auto
    flush() -> void;

    //
    // Gets the logger initialization status.
    //
    static
    auto
    is_logger_initialized() -> bool;  

private:

    //
    // Constructor for the singleton instance. Internal use only.
    //
    logger();

    //
    // Initializes the singleton logger instance. Internal use only.
    //
    auto
    initialize(
        const logger_configuration* p_logger_configuration) -> status_code;

    //
    // Logging engine used to handle logs dispatching.
    //
    logging_engine m_logging_engine;

    //
    // Flag for determining if the singleton instance is initialized.
    //
    static std::atomic<bool> s_initialized;

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