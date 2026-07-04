#pragma once
/**
\file       events-storage-base-types.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
\project    u3_events_storage
*/

namespace libs::events_storage
{
//  ext types
using path_id_type   = std::string;                     //<
using stream_id_type = ::libs::utility::utils::cuuid;   //<
}   // namespace libs::events_storage
