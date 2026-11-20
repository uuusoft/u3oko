#pragma once
/**
\file       buf-event-vec2image1.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace libs::events_base::props::videos::generic::vec2image::syn
{
using off_buf_type            = ::utils::dbufs::video::consts::offs::off_buf_type;
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
}   // namespace libs::events_base::props::videos::generic::vec2image::syn


namespace libs::events_base::props::videos::generic::vec2image
{
struct EventBufsVec2Image1 final : public ::libs::events::buf::EventBufs {
  friend class boost::serialization::access;

  public:
  explicit EventBufsVec2Image1 (
    const syn::off_buf_type src = utils::dbufs::video::consts::offs::invalid,
    const syn::off_buf_type dst = utils::dbufs::video::consts::offs::invalid);

  explicit EventBufsVec2Image1 (const ::libs::events::buf::EventBufs& buf);

  std::int32_t size_block_ { 16 };     //< Размер блока в пикселях, в который конвертируется вектор
  std::int32_t mul_koeff_vec_ { 1 };   //< Опциональный коэффициент для масштабирования векторов

  protected:
  virtual void check_int () override;
  virtual void correct_int () override;

  private:
  U3_ADD_SUPER_CLASS (::libs::events::buf::EventBufs)

  friend class boost::serialization::access;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);
};

auto tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const EventBufsVec2Image1& src) -> void;
auto tag_invoke (::boost::json::value_to_tag< EventBufsVec2Image1 >, const ::boost::json::value& jvs) -> EventBufsVec2Image1;
}   // namespace libs::events_base::props::videos::generic::vec2image

U3_BOOST_CLASS_EXPORT_KEY (::libs::events_base::props::videos::generic::vec2image::EventBufsVec2Image1);
