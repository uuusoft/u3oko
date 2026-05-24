#pragma once
/**
\file       type-scaler.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       18.06.2022
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::scaler
{
enum class Scalers : std::uint32_t
{
  nearest     = 0x00,   //<
  bilinear    = 0x01,   //<
  fixed_pow2  = 0x02,   //<
  simple_copy = 0x03,   //<
  unknown     = 0xFF    //<
};

Scalers     str2scaler_type (const std::string& str);
std::string to_string (const Scalers& val);
void        tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const Scalers& src);
Scalers     tag_invoke (::boost::json::value_to_tag< Scalers >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::scaler
