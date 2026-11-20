#pragma once
/**
\file       events-storage-const-vals.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.07.2018
*/

namespace libs::events_storage::consts
{
extern const stream_id_type empty_stream_id;

inline constexpr std::string_view empty_object_id { "" };
}   // namespace libs::events_storage::consts
