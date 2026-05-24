#pragma once
/**
\file       out-channel-info.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.09.2018
\project    u3_ievents_lib
*/

namespace libs::ievents::props::mix_mul::consts
{
constexpr std::int32_t max_input_points  = 16;   //<
constexpr std::int32_t max_output_points = 16;   //<
}   // namespace libs::ievents::props::mix_mul::consts


namespace libs::ievents::props::mix_mul
{
struct OutChannelInfo final {
  // ext types
  using src2dst_bufs_type = std::vector< ::libs::events::buf::EventBufsInfo >;

  OutChannelInfo ();
  virtual ~OutChannelInfo ();

  src2dst_bufs_type srcs2dsts_;   //<

  private:
  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void           tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const OutChannelInfo& src);
OutChannelInfo tag_invoke (::boost::json::value_to_tag< OutChannelInfo >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::mix_mul::OutChannelInfo);
