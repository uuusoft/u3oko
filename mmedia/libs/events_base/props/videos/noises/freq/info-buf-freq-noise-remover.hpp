#pragma once
/**
\file       info-buf-freq-noise-remover.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
namespace libs::events_base::props::videos::noises::freq::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;

namespace offs = ::utils::dbufs::video::consts::offs;
}   // namespace libs::events_base::props::videos::noises::freq::syn

namespace libs::events_base::props::videos::noises::freq
{
struct InfoBuffFreqNoiseRemover final : public ::libs::events::buf::EventBufs {
  // ext types
  U3_ADD_POINTERS_TO_SELF (InfoBuffFreqNoiseRemover)

  InfoBuffFreqNoiseRemover (
    const syn::off_buf_type& src            = syn::offs::invalid,
    const syn::off_buf_type& dst            = syn::offs::invalid,
    syn::off_buf_type        bindx_diff     = syn::offs::invalid,
    std::int16_t             bound_x_plus_y = 1,
    float                    dwt_koeff2     = 1.0F);

  explicit InfoBuffFreqNoiseRemover (const ::libs::events::buf::EventBufs& buf);

  syn::off_buf_type bindx_diff_     = syn::offs::invalid;   //<
  std::int16_t      bound_x_plus_y_ = 1;                    //<
  float             dwt_koeff2_     = 1.0F;                 //<

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoBuffFreqNoiseRemover& src);
InfoBuffFreqNoiseRemover tag_invoke (::boost::json::value_to_tag< InfoBuffFreqNoiseRemover >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::noises::freq

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::noises::freq::InfoBuffFreqNoiseRemover);
