/**
\file       morph-operation-type.cpp
\date       08.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "morph-operation-type.hpp"

namespace libs::ievents::props::videos::generic::morph
{
MorphOps
str2type_morph_op (const std::string& txt)
{
  const std::pair< std::string, MorphOps > ops[] = {
    std::pair< std::string, MorphOps > ("erosion", MorphOps::erosion),
    std::pair< std::string, MorphOps > ("dilation", MorphOps::dilation),
    std::pair< std::string, MorphOps > ("binary", MorphOps::binary),
    std::pair< std::string, MorphOps > ("skip", MorphOps::empty)
  };

  for (const auto& op : ops)
  {
    if (op.first == txt)
    {
      return op.second;
    }
  }
  U3_XLOG_WARN ("unknown text id MorphOps " + txt);
  return MorphOps::empty;
}


std::string
to_string (const MorphOps& val)
{
  const std::unordered_map< MorphOps, const std::string > ops = {
    { MorphOps::erosion, "erosion" },
    { MorphOps::dilation, "dilation" },
    { MorphOps::binary, "binary" },
    { MorphOps::empty, "skip" },
    { MorphOps::unknown, "unknown" }
  };

  auto find = ops.find (val);
  if (ops.end () == find)
  {
    U3_XLOG_ERROR ("unknown LogLevels" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
    return "unknown MorphOps";
  }
  return find->second;
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const MorphOps& src)
{
  jv = { "morph_operation", U3_CAST_UINT32_FORCE (src) };
}


MorphOps
tag_invoke (::boost::json::value_to_tag< MorphOps >, const ::boost::json::value& jv)
{
  return U3_CAST_STATIC< MorphOps > (::libs::helpers::json::get_uint32 (jv));
}
}   // namespace libs::ievents::props::videos::generic::morph
