#pragma once
/**
\file       buf-event-info-vec2image1.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/

namespace libs::ievents::props::videos::generic::vec2image
{
struct EventBufsInfoVec2Image1 final : public ::libs::events::buf::EventBufsInfo {
  friend class boost::serialization::access;

  public:
  explicit EventBufsInfoVec2Image1 (
    const ::utils::dbufs::video::consts::offs::off_buf_type& src = utils::dbufs::video::consts::offs::invalid,
    const ::utils::dbufs::video::consts::offs::off_buf_type& dst = utils::dbufs::video::consts::offs::invalid);

  explicit EventBufsInfoVec2Image1 (const ::libs::events::buf::EventBufsInfo& buf);

  std::int32_t size_block_;      //< Размер блока в пикселях, в который конвертируется вектор
  std::int32_t mul_koeff_vec_;   //< Опциональный коэффициент для масштабирования векторов

  protected:
  virtual void check_int () override;
  virtual void correct_int () override;

  private:
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::events::buf::EventBufsInfo)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);
};

void                    tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const EventBufsInfoVec2Image1& src);
EventBufsInfoVec2Image1 tag_invoke (::boost::json::value_to_tag< EventBufsInfoVec2Image1 >, const ::boost::json::value& jv);
}   // namespace libs::ievents::props::videos::generic::vec2image

BOOST_CLASS_EXPORT_KEY (::libs::ievents::props::videos::generic::vec2image::EventBufsInfoVec2Image1);
