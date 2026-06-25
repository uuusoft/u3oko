#pragma once
/**
\file       buf-event-info-video-scaler.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::scaler
{
struct EventBufsInfoVideoScaler final : public ::libs::events::buf::EventBufsInfo {
  friend class boost::serialization::access;

  public:
  explicit EventBufsInfoVideoScaler (
    const ::utils::dbufs::video::consts::offs::off_buf_type& src = utils::dbufs::video::consts::offs::invalid,
    const ::utils::dbufs::video::consts::offs::off_buf_type& dst = utils::dbufs::video::consts::offs::invalid);

  explicit EventBufsInfoVideoScaler (const ::libs::events::buf::EventBufsInfo& buf);

  Scalers                              type_;         //< тип масштабирования
  std::int32_t                         koeff_pow2_;   //< Степень двойки для режима Scalers::fixed_pow2
  ::libs::events::props::details::Rect src_rect_;     //< Прямоугльник источника
  ::libs::events::props::details::Rect dst_rect_;     //< Прямогульник назначения

  protected:
  // virtual void check_int () override;
  // virtual void load_int (const ::pugi::xml_named_node_iterator& node) override;
  // virtual void correct_int () override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buf::EventBufsInfo)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

void                     tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const EventBufsInfoVideoScaler& src);
EventBufsInfoVideoScaler tag_invoke (::boost::json::value_to_tag< EventBufsInfoVideoScaler >, const ::boost::json::value& jvs);
}   // namespace libs::ievents::props::videos::generic::scaler

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::scaler::EventBufsInfoVideoScaler);
