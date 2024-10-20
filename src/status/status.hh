// ****************************************************
// Echo Logger C++ Library
// Status
// 'status.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <cstdint>

namespace echo
{

//
// Status code type alias.
//
using status_code = std::uint32_t;

namespace status
{

//
// Status code definition macro.
//
#define status_code_definition(p_status_code_name, p_status_code_value) static constexpr status_code p_status_code_name = p_status_code_value

//
// Operation succeeded.
//
status_code_definition(success, 0x0'0000000);

//
// Generic operation failed.
//
status_code_definition(fail, 0x8'0000000);

//
// Determines whether a given status is considered as failure.
//
inline
auto
failed(
    const status_code p_status_code) -> bool
{
    return static_cast<std::int32_t>(p_status_code) < 0;
}

//
// Determines whether a given status is considered as success.
//
inline
auto
succeeded(
    const status_code& p_status_code) -> bool
{
    return p_status_code == success;
}

//
// Determines whether a given status is the same as another status.
//
inline
auto
are_equal(
    const status_code& p_status_code_left,
    const status_code& p_status_code_right) -> bool
{
    return p_status_code_left == p_status_code_right;
}

//
// Determines whether a given status is not the same as another status.
//
inline
auto
are_not_equal(
    const status_code& p_status_code_left,
    const status_code& p_status_code_right) -> bool
{
    return p_status_code_left != p_status_code_right;
}

/*
//
// Library-defined status codes.
//
*/

//
// Logger is not yet initialized.
//
status_code_definition(logger_not_initialized, 0x8'0000001);

//
// Logger is already initialized.
//
status_code_definition(logger_already_initialized, 0x8'0000002);

//
// Incorrect parameters.
//
status_code_definition(incorrect_parameters, 0x8'0000003);

//
// Failure to create a directory.
//
status_code_definition(directory_creation_failed, 0x8'0000004);

//
// Failure to retrieve an environment variable.
//
status_code_definition(environment_variable_access_failed, 0x8'0000005);

//
// Failed to write to a file.
//
status_code_definition(file_write_failed, 0x8'0000006);

//
// Failed to log to a file because incremental search reached its retry limit.
//
status_code_definition(logging_incremental_search_failed, 0x8'0000007);

} // namespace status.
} // namespace echo.