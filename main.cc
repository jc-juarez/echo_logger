#include "src/logger/logger.hh"

int main()
{
    syp::logger::initialize();

    syp::logger::log(syp::log_level::warning,
        "Main",
        "Hello World! {}, {}",
        45,
        37+2);

    syp::logger::flush();
}