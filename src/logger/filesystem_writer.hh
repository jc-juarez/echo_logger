// ****************************************************
// Echo Logger C++ Library
// Logger
// 'filesystem_writer.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <filesystem>
#include "../status/status.hh"

namespace echo
{

//
// Filesystem writer class for handling logs dispatching to disk.
//
class filesystem_writer
{

public:

    //
    // Constructor.
    //
    filesystem_writer();

private:

    //
    // Creates and/or appends data to the specified file.
    //
    static
    auto
    write_to_file(
        const std::filesystem::path& p_file_path,
        const char* p_data_buffer) -> status_code;

};

} // namespace echo.