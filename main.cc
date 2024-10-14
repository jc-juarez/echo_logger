#include "src/logger/logger.hh"

namespace foo
{
void func()
{
    syp::logger::log(syp::log_level::warning,
        "Main",
        "Hello World! {}, {}",
        45,
        37+2);
}
}

int main()
{
    syp::logger::initialize();

    foo::func();

    syp::logger::flush();
}