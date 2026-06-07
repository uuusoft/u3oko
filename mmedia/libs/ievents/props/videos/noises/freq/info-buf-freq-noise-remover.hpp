#pragma once
/**
\file       info-buf-freq-noise-remover.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::noises::freq
{
struct InfoBuffFreqNoiseRemover final : public ::libs::events::buf::EventBufsInfo {
  // ext types
  U3_HELPER_THIS_TYPE_HAS_POINTERS_TO_SELF (InfoBuffFreqNoiseRemover)

  InfoBuffFreqNoiseRemover (
    const ::utils::dbufs::video::consts::offs::off_buf_type& src            = utils::dbufs::video::consts::offs::invalid,
    const ::utils::dbufs::video::consts::offs::off_buf_type& dst            = utils::dbufs::video::consts::offs::invalid,
    const ::utils::dbufs::video::consts::offs::off_buf_type& bindx_diff     = utils::dbufs::video::consts::offs::invalid,
    std::int16_t                                             bound_x_plus_y = 1,
    float                                                    dwt_koeff2     = 1.0F);

  explicit InfoBuffFreqNoiseRemover (const ::libs::events::buf::EventBufsInfo& buf);

  ::utils::dbufs::video::consts::offs::off_buf_type bindx_diff_;       //<
  std::int16_t                                      bound_x_plus_y_;   //<
  float                                             dwt_koeff2_;       //<

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoBuffFreqNoiseRemover& src);
InfoBuffFreqNoiseRemover tag_invoke (::boost::json::value_to_tag< InfoBuffFreqNoiseRemover >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
