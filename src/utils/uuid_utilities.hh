// ****************************************************
// Echo Logger C++ Library
// Utils
// 'uuid_utilities.hh'
// Author: jcjuarez
// This source code is licensed under the MIT license.
// ****************************************************

#pragma once

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

namespace echo
{

//
// Generates a new UUID.
// Thread-safe function.
//
auto
generate_uuid() -> boost::uuids::uuid;

inline
auto
uuid_to_string(
    const boost::uuids::uuid p_uuid) -> std::string
{
    return boost::uuids::to_string(p_uuid);
}

} // namespace echo.