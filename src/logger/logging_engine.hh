// ****************************************************
// Synapse C++ Library
// Logger
// 'logging_engine.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include "log_level.hh"
#include "../status/status.hh"
#include "logger_configuration.hh"

namespace syp
{

//
// Logging engine used for logs memory placement and filesystem flushing.
//
class logging_engine
{

public:

    logging_engine();

    auto
    initialize(
        const logger_configuration& p_logger_configuration) -> status_code;

    auto
    log(
        const log_level& p_log_level,
        const char* p_title,
        const char* p_message) -> void;

};

} // namespace syp.