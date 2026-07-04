/**
\file       enum-morph-ops.cpp
\date       08.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "enum-morph-ops.hpp"

namespace libs::events_base::props::videos::generic::morph
{
auto
str2type_morph_op (const std::string& val) -> MorphOps
{
  static const boost::unordered_flat_map< std::string, const MorphOps > vals = {
    { "erosion", MorphOps::erosion },
    { "dilation", MorphOps::dilation },
    { "binary", MorphOps::binary },
    { "skip", MorphOps::empty },
    { "unknown", MorphOps::unknown }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find morph type");
    finger = vals.find ("skip");
  }
  return finger->second;
}


auto
to_string (const MorphOps& val) -> const std::string&
{
  static const boost::unordered_flat_map< MorphOps, const std::string > vals = {
    { MorphOps::erosion, "erosion" },
    { MorphOps::dilation, "dilation" },
    { MorphOps::binary, "binary" },
    { MorphOps::empty, "skip" },
    { MorphOps::unknown, "unknown" }
  };

  auto finger = vals.find (val);
  if (vals.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find name morph type");
    finger = vals.find (MorphOps::empty);
  }
  return finger->second;
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const MorphOps& src)
{
  jvs = { "morph_operation", U3_CAST_UINT32_FORCE (src) };
}


auto
tag_invoke (::boost::json::value_to_tag< MorphOps >, const ::boost::json::value& jvs) -> MorphOps
{
  return ::libs::utility::casts::static_cast_helper< MorphOps > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base::props::videos::generic::morph
