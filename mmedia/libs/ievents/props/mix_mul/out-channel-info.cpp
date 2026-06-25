/**
\file       out-channel-info.cpp
\author     Erashov Anton erashov2026@proton.me
\date       17.06.2022
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "out-channel-info.hpp"

namespace libs::ievents::props::mix_mul
{
template< class Archive >
void
OutChannelInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (srcs2dsts_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const OutChannelInfo& src)
{
  jvs = { { "srcs2dsts", boost::json::value_from (src.srcs2dsts_) } };
}


OutChannelInfo
tag_invoke (::boost::json::value_to_tag< OutChannelInfo >, const ::boost::json::value& jvs)
{
  OutChannelInfo ret;

  ret.srcs2dsts_ = ::boost::json::value_to< OutChannelInfo::src2dst_bufs_type > (jvs.at ("srcs2dsts"));
  return ret;
}
}   // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::mix_mul::OutChannelInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::mix_mul::OutChannelInfo);
