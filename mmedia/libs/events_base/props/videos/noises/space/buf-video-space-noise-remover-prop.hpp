#pragma once
/**
\file       buf-video-space-noise-remover-prop.hpp
\date       01.04.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
namespace libs::events_base::props::videos::noises::space::syn
{
using off_buf_type = ::utils::dbufs::video::consts::offs::off_buf_type;

namespace offs = ::utils::dbufs::video::consts::offs;
}   // namespace libs::events_base::props::videos::noises::space::syn

namespace libs::events_base::props::videos::noises::space
{
struct BuffVideoSpaceNoiseRemoverProp final : public ::libs::events::buf::EventBufs {
  public:
  explicit BuffVideoSpaceNoiseRemoverProp (
    const syn::off_buf_type& src = syn::offs::invalid,
    const syn::off_buf_type& dst = syn::offs::invalid);

  explicit BuffVideoSpaceNoiseRemoverProp (const ::libs::events::buf::EventBufs& buf);

  ::libs::events::IEvent::ptr impl_info_;   //< Расширенные свойства, связанные с конкретной реализацией фильтрации

  protected:
  // overrides ::libs::events::buf::EventBufs
  virtual void check_int () override;
  virtual void correct_int () override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events::buf::EventBufs)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                           tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const BuffVideoSpaceNoiseRemoverProp& src);
BuffVideoSpaceNoiseRemoverProp tag_invoke (::boost::json::value_to_tag< BuffVideoSpaceNoiseRemoverProp >, const ::boost::json::value& jvs);
}   // namespace libs::events_base::props::videos::noises::space

BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::noises::space::BuffVideoSpaceNoiseRemoverProp);
