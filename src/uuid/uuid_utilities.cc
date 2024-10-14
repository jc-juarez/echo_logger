// ****************************************************
// Synapse C++ Library
// UUID
// 'uuid_utilities.cc'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#include "uuid_utilities.hh"

namespace syp
{

auto
generate_uuid() -> uuid
{
    thread_local boost::uuids::random_generator uuid_generator;

    return uuid_generator();
}

} // namespace syp.