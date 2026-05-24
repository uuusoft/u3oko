/**
\file       type-scaler.cpp
\date       18.06.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "type-scaler.hpp"

namespace libs::ievents::props::videos::generic::scaler
{
Scalers
str2scaler_type (const std::string& str)
{
  const std::pair< std::string, const Scalers > vals[] = {
    std::pair< std::string, Scalers > ("nearest", Scalers::nearest),
    std::pair< std::string, Scalers > ("bilinear", Scalers::bilinear),
    std::pair< std::string, Scalers > ("fixed_pow2", Scalers::fixed_pow2),
    std::pair< std::string, Scalers > ("simple_copy", Scalers::simple_copy),
  };

  for (const auto& val : vals)
  {
    if (val.first == str)
    {
      return val.second;
    }
  }

  U3_ASSERT_SIGNAL_NT ("failed");
  return Scalers::nearest;
}


std::string
to_string (const Scalers& val)
{
  const std::pair< Scalers, const std::string > vals[] = {
    { Scalers::nearest, "nearest" },
    std::pair< Scalers, std::string > (Scalers::bilinear, "bilinear"),
    std::pair< Scalers, std::string > (Scalers::fixed_pow2, "fixed_pow2"),
    std::pair< Scalers, std::string > (Scalers::simple_copy, "simple_copy"),
    std::pair< Scalers, std::string > (Scalers::unknown, "unknown")
  };

  for (const auto& nval : vals)
  {
    if (nval.first == val)
    {
      return nval.second;
    }
  }

  U3_XLOG_ERROR ("unknown Scalers" + VTOLOG (U3_CAST_UINT32_FORCE (val)));
  return "unknown Scalers";
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const Scalers& src)
{
  jv = U3_CAST_UINT32_FORCE (src);
}


Scalers
tag_invoke (::boost::json::value_to_tag< Scalers >, const ::boost::json::value& jv)
{
  return U3_CAST_STATIC< Scalers > (::libs::helpers::json::get_uint32 (jv));
}
}   // namespace libs::ievents::props::videos::generic::scaler
