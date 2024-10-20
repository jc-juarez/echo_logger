// ****************************************************
// Echo Logger C++ Library
// Logger
// 'filesystem_writer.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <mutex>
#include <cstdint>
#include <optional>
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
    filesystem_writer(
        const std::string& p_session_id,
        const std::filesystem::path& p_logging_session_directory_path);

    //
    // Provides a direct API for writing a single log message to disk.
    //
    auto
    write_log_message_to_disk(
        const char* p_log_message) -> status_code;

private:

    //
    // Generates the curently pointed logs file path.
    //
    auto
    get_pointed_logs_file_path() const -> std::filesystem::path;

    //
    // Creates and/or appends data to the specified file.
    //
    static
    auto
    write_to_file(
        const std::filesystem::path& p_file_path,
        const char* p_data_buffer) -> status_code;

    //
    // Gets the size of a file in MiB.
    //
    static
    auto
    get_file_size_in_mib(
        const std::filesystem::path& p_file_path) -> std::optional<std::uint32_t>;

    //
    // Logs files extension.
    //
    static constexpr const char* c_logs_files_extension = "log";

    //
    // Max size in MiB for individual logs files.
    //
    static constexpr std::uint8_t c_max_logs_file_size_mib = 10u;

    //
    // Max retries count for incremental search for logging.
    //
    static constexpr std::uint8_t c_max_incremental_search_retry_count = 5u;

    //
    // Max retries count for logs writing attempts.
    //
    static constexpr std::uint8_t c_max_logs_writing_attempts_retry_count = 10u;

    //
    // Logging session identifier.
    //
    const std::string m_session_id;

    //
    // Logs files count.  
    //
    std::uint64_t m_logs_files_count;

    //
    // Path to the directory where the logs for the logging session will be stored.
    //
    const std::filesystem::path m_logging_session_directory_path;

    //
    // Path to the currently pointed logs file.
    //
    std::filesystem::path m_pointed_logs_file_path;

    //
    // Lock for synchronizing pointed logs file internal metadata.
    //
    mutable std::mutex m_pointed_logs_file_lock;

};

} // namespace echo.