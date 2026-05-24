/**
\file       istorage-events-const-vals.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       09.02.2026
\project    u3_istorage_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../istorage-events-includes_int.hpp"
#include "istorage-events-const-vals.hpp"

namespace libs::istorage_events::consts
{
const stream_id_type empty_stream_id (::boost::uuids::nil_uuid ());
const char*          empty_object_id = "";
}   // namespace libs::istorage_events::consts
