#include "src/logger/logger.hh"

namespace foo
{
void func()
{
    echo::logger::log(echo::log_level::warning,
        "Main",
        "Hello World! {}, {}",
        45,
        37+2);
}
}

int main()
{
    echo::logger_configuration config;

    config.flush_frequency_ms = 10'000;
    config.component_name = "NexusMasterIndex";
    config.logs_directory_path = "/home/jcjuarez/NexusMasterIndexLogs";

    echo::logger::initialize(&config);

    foo::func();

    echo::logger::flush();
}