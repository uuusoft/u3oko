/**
\file       type-scaler.cpp
\date       18.06.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "type-scaler.hpp"

namespace libs::events_base::props::videos::generic::scaler
{
auto
str2scaler_type (const std::string& str) -> Scalers
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


auto
to_string (const Scalers& val) -> std::string
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
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const Scalers& src)
{
  jvs = U3_CAST_UINT32_FORCE (src);
}


auto
tag_invoke (::boost::json::value_to_tag< Scalers >, const ::boost::json::value& jvs) -> Scalers
{
  return ::libs::utility::casts::static_cast_helper< Scalers > (::libs::utility::json::get_uint32 (jvs));
}
}   // namespace libs::events_base::props::videos::generic::scaler
