#pragma once
/**
\file       checkers-enum.hpp
\date       15.08.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::modules::storage
{
enum class Checkers : std::uint32_t
{
  disabled                    = 0x00,   //<
  start_stop                  = 0x01,   //<
  periodicaly                 = 0x02,   //<
  after_every_write_operation = 0x03,   //<
  unknown                     = 0xFF    //<
};

Checkers str2checker_storage (const std::string& str);
void     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Checkers& src);
Checkers tag_invoke (::boost::json::value_to_tag< Checkers >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::modules::storage
