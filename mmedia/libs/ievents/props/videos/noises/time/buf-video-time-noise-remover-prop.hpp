#pragma once
/**
\file       buf-video-time-noise-remover-prop.hpp
\date       01.07.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
namespace libs::ievents::props::videos::noises::time::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;

namespace offs = ::utils::dbufs::video::consts::offs;
}   // namespace libs::ievents::props::videos::noises::time::syn

namespace libs::ievents::props::videos::noises::time
{
struct BuffVideoTimeNoiseRemoverProp final : public ::libs::events::buf::EventBufsInfo {
  public:
  explicit BuffVideoTimeNoiseRemoverProp (
    const syn::off_buf_type& src = syn::offs::invalid,
    const syn::off_buf_type& dst = syn::offs::invalid);

  explicit BuffVideoTimeNoiseRemoverProp (const ::libs::events::buf::EventBufsInfo& buf);

  ::libs::events::IEvent::ptr impl_info_;   //< Расширенные свойства, связанные с конкретной реализацией фильтрации

  protected:
  // overrides ::libs::events::buf::EventBufsInfo
  virtual void check_int () override;
  virtual void correct_int () override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buf::EventBufsInfo)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                          tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const BuffVideoTimeNoiseRemoverProp& src);
BuffVideoTimeNoiseRemoverProp tag_invoke (::boost::json::value_to_tag< BuffVideoTimeNoiseRemoverProp >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::noises::time

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::noises::time::BuffVideoTimeNoiseRemoverProp);
