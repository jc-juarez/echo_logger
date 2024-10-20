// ****************************************************
// Echo Logger C++ Library
// Utils
// 'uuid_utilities.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include "uuid_utilities.hh"

namespace echo
{

auto
generate_uuid() -> boost::uuids::uuid
{
    thread_local boost::uuids::random_generator uuid_generator;

    return uuid_generator();
}

} // namespace echo.