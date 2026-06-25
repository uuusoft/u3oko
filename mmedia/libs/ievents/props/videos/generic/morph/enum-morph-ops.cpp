/**
\file       enum-morph-ops.cpp
\date       08.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "enum-morph-ops.hpp"

namespace libs::ievents::props::videos::generic::morph
{
MorphOps
str2type_morph_op (const std::string& val)
{
  static const std::unordered_map< std::string, const MorphOps > vals = {
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


const std::string&
to_string (const MorphOps& val)
{
  static const std::unordered_map< MorphOps, const std::string > vals = {
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


MorphOps
tag_invoke (::boost::json::value_to_tag< MorphOps >, const ::boost::json::value& jvs)
{
  return ::libs::helpers::casts::static_cast_helper< MorphOps > (::libs::helpers::json::get_uint32 (jvs));
}
}   // namespace libs::ievents::props::videos::generic::morph
