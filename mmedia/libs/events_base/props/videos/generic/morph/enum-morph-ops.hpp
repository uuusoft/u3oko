#pragma once
/**
\file       enum-morph-ops.hpp
\date       10.09.2018
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/

namespace libs::events_base::props::videos::generic::morph
{
enum class MorphOps : std::uint32_t
{
  empty    = 0x00,   //<
  erosion  = 0x01,   //<
  dilation = 0x02,   //<
  binary   = 0x04,   //<
  unknown  = 0xFF    //<
};

MorphOps           str2type_morph_op (const std::string& txt);
const std::string& to_string (const MorphOps& val);
void               tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const MorphOps& src);
MorphOps           tag_invoke (::boost::json::value_to_tag< MorphOps >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::generic::morph
