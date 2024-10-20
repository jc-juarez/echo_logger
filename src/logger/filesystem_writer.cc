// ****************************************************
// Echo Logger C++ Library
// Logger
// 'filesystem_writer.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include <fstream>
#include "filesystem_writer.hh"

namespace echo
{

filesystem_writer::filesystem_writer()
{}

auto
filesystem_writer::write_to_file(
    const std::filesystem::path& p_file_path,
    const char* p_data_buffer) -> status_code
{
    std::ofstream file;

    file.open(p_file_path, std::ios_base::app);

    if (!file)
    {
        return status::file_write_failed;
    }

    file << p_data_buffer;

    return status::success;
}

} // namespace echo.