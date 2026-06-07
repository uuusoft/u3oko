/**
\file       enum-morph-ops.cpp
\date       08.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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
  static const std::unordered_map< std::string, const MorphOps > val2val = {
    { "erosion", MorphOps::erosion },
    { "dilation", MorphOps::dilation },
    { "binary", MorphOps::binary },
    { "skip", MorphOps::empty },
    { "unknown", MorphOps::unknown }
  };

  auto finger = val2val.find (val);
  if (val2val.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find morph type");
    finger = val2val.find ("skip");
  }
  return finger->second;
}


const std::string&
to_string (const MorphOps& val)
{
  static const std::unordered_map< MorphOps, const std::string > val2val = {
    { MorphOps::erosion, "erosion" },
    { MorphOps::dilation, "dilation" },
    { MorphOps::binary, "binary" },
    { MorphOps::empty, "skip" },
    { MorphOps::unknown, "unknown" }
  };

  auto finger = val2val.find (val);
  if (val2val.end () == finger)
  {
    U3_ASSERT_SIGNAL_NT ("failed find name morph type");
    finger = val2val.find (MorphOps::empty);
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
