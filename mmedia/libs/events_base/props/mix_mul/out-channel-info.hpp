#pragma once
/**
\file       out-channel-info.hpp
\author     Erashov Anton erashov2026@proton.me
\date       14.09.2018
\project    u3_events_base_lib
*/

namespace libs::events_base::props::mix_mul::consts
{
inline constexpr std::int32_t max_input_points  = 16;   //<
inline constexpr std::int32_t max_output_points = 16;   //<
}   // namespace libs::events_base::props::mix_mul::consts


namespace libs::events_base::props::mix_mul
{
struct OutChannelInfo final {
  // ext types
  using src2dst_bufs_type = std::vector< ::libs::events::buf::EventBufs >;

  OutChannelInfo ()          = default;
  virtual ~OutChannelInfo () = default;

  src2dst_bufs_type srcs2dsts_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void           tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const OutChannelInfo& src);
OutChannelInfo tag_invoke (::boost::json::value_to_tag< OutChannelInfo >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::mix_mul

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::mix_mul::OutChannelInfo);
