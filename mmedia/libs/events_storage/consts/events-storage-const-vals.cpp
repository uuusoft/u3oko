/**
\file       events-storage-const-vals.cpp
\author     Erashov Anton erashov2026@proton.me
\date       09.02.2026
\project    u3_events_storage
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../events-storage-includes_int.hpp"
#include "events-storage-const-vals.hpp"

namespace libs::events_storage::consts
{
const stream_id_type empty_stream_id (::boost::uuids::nil_uuid ());
const char*          empty_object_id = "";
}   // namespace libs::events_storage::consts
