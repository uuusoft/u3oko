/**
\file       events-modules-log-vals.cpp
\date       07.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "events-modules-log-vals.hpp"

namespace libs::events_base::props::modules::log::consts
{
const char* max_cache_events              = "max-cache-events";
const char* ms_max_period_flush_events    = "ms-max-period-flush-events";
const char* max_size_one_log_file_byte    = "max-size-one-log-file-byte";
const char* enable_store_call_place       = "enable-store-call-place";
const char* enable_log_events             = "enable-log-events";
const char* log_level                     = "log-level";
const char* enable_suppress_duplicate_msg = "enable-suppress-duplicate-msg";
const char* no_val                        = "\0";
}   // namespace libs::events_base::props::modules::log::consts
