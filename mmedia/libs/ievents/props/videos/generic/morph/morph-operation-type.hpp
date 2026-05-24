#pragma once
/**
\file       morph-operation-type.hpp
\date       10.09.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::morph
{
enum class MorphOps : std::uint32_t
{
  empty    = 0x00,   //<
  erosion  = 0x01,   //<
  dilation = 0x02,   //<
  binary   = 0x04,   //<
  unknown  = 0xFF    //<
};

MorphOps    str2type_morph_op (const std::string& txt);
std::string to_string (const MorphOps& val);
void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const MorphOps& src);
MorphOps    tag_invoke (::boost::json::value_to_tag< MorphOps >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::morph
