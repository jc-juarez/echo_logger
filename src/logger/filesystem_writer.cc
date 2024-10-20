// ****************************************************
// Echo Logger C++ Library
// Logger
// 'filesystem_writer.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include <format>
#include <fstream>
#include "filesystem_writer.hh"

namespace echo
{

filesystem_writer::filesystem_writer(
    const std::string& p_session_id,
    const std::filesystem::path& p_logging_session_directory_path)
    : m_logs_files_count{0},
      m_session_id{p_session_id},
      m_logging_session_directory_path{p_logging_session_directory_path},
      m_pointed_logs_file_path{get_pointed_logs_file_path()}
{}

/*
The Lord Speaks.

“Brace yourself like a man;
    I will question you,
    and you shall answer me.
Can you bind the chains of the Pleiades?
    Can you loosen Orion’s belt?
Can you bring forth the constellations in their seasons
    or lead out the Bear with its cubs?
Do you know the laws of the heavens?"
*/

auto
filesystem_writer::write_log_message_to_disk(
    const char* p_log_message) -> status_code
{
    //
    // Idemponent logging even if the directory is not present.
    //
    if (!std::filesystem::exists(m_logging_session_directory_path))
    {
        try
        {
            std::filesystem::create_directories(m_logging_session_directory_path);
        }
        catch(const std::exception& p_exception)
        {
            //
            // No exceptions allowed in the logging hotpath; handle the error gracefully.
            //
            return status::directory_creation_failed;
        }
    }

    //
    // Incremental search for determining the file on which to log the message. Performance of
    // this logging mechanism can be impacted if other processes interfere with the directory.
    // In case of continuous errors that exceed a retry limit, the operation is considered failed.
    //
    for (std::uint16_t incremental_search_retry_count {1}; incremental_search_retry_count <= c_max_incremental_search_retry_count; ++incremental_search_retry_count)
    {
        status_code creation_status = status::success;

        if (!std::filesystem::exists(m_pointed_logs_file_path))
        {
            //
            // This will create the pointed logs file. Do not inspect the
            // result of creation. This is already handled in the below path.
            //
            creation_status = write_to_file(
                m_pointed_logs_file_path,
                nullptr /* p_data_buffer */);
        }

        //
        // If the file exists ensure that it has not exceeded the size limit; if it 
        // has, rollover the logs file count and switch the currently pointed logs file.
        //
        if (status::succeeded(creation_status))
        {
            const std::optional<std::uint32_t> file_size_mib = get_file_size_in_mib(m_pointed_logs_file_path);

            if (file_size_mib.has_value() &&
                file_size_mib.value() < c_max_logs_file_size_mib)
            {
                for (std::uint16_t logs_writing_attempts_retry_count {1}; logs_writing_attempts_retry_count <= c_max_logs_writing_attempts_retry_count; ++logs_writing_attempts_retry_count)
                {
                    const status_code status = write_to_file(
                        m_pointed_logs_file_path,
                        p_log_message);

                    if (status::failed(status))
                    {
                        //
                        // Filesystem error write detected. Operation will be retried.
                        //
                        continue;
                    }

                    //
                    // Filesystem write succeeded. Exit.
                    //
                    return status::success;
                }
            }
        }

        if (incremental_search_retry_count == c_max_incremental_search_retry_count)
        {
            return status::logging_incremental_search_failed;
        }

        {
            //
            // The contention produced by this is minimal as this is executed when the pointed logs
            // file needs to be shifted because of its file size or unexpected filesystem write errors.
            //
            std::scoped_lock<std::mutex> lock {m_pointed_logs_file_lock};

            ++m_logs_files_count;
            m_pointed_logs_file_path = get_pointed_logs_file_path();
        }
    }

    //
    // Unreachable.
    //
    return status::fail;
}

auto
filesystem_writer::get_pointed_logs_file_path() const -> std::filesystem::path
{
    const std::string pointed_logs_file_name = std::format(
        "log_{}_{}.{}",
        m_session_id,
        m_logs_files_count,
        c_logs_files_extension);

    return m_logging_session_directory_path / pointed_logs_file_name;
}

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

auto
filesystem_writer::get_file_size_in_mib(
    const std::filesystem::path& p_file_path) -> std::optional<std::uint32_t>
{
    try
    {
        const std::uint32_t file_size_bytes = static_cast<std::uint32_t>(std::filesystem::file_size(p_file_path));
        return file_size_bytes / (1024u * 1024u);
    }
    catch (const std::filesystem::filesystem_error& exception)
    {
        //
        // This method is used in the logging hotpath where no exceptions
        // are allowed. Consider a failed retrieval as an invalid value.
        //
        return std::nullopt;
    }
}

} // namespace echo.