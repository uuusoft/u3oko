/**
\file       buf-event-info-vec2image1.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "buf-event-info-vec2image1.hpp"

namespace libs::ievents::props::videos::generic::vec2image
{
EventBufsInfoVec2Image1::EventBufsInfoVec2Image1 (
  const ::utils::dbufs::video::consts::offs::off_buf_type& src,
  const ::utils::dbufs::video::consts::offs::off_buf_type& dst) :

  ::libs::events::buf::EventBufsInfo (src, dst),
  size_block_ (16),
  mul_koeff_vec_ (1)
{
}


EventBufsInfoVec2Image1::EventBufsInfoVec2Image1 (const ::libs::events::buf::EventBufsInfo& buf) :
  ::libs::events::buf::EventBufsInfo (buf),
  size_block_ (16),
  mul_koeff_vec_ (1)
{
}


void
EventBufsInfoVec2Image1::check_int ()
{
  U3_CHECK (8 == size_block_ || 16 == size_block_ || 32 == size_block_, "size block invalid");
  U3_CHECK (mul_koeff_vec_ > 0, "mul koeff less 0");
}


void
EventBufsInfoVec2Image1::correct_int ()
{
  if (size_block_ != 8 && size_block_ != 16 && size_block_ != 32)
  {
    size_block_ = 8;
  }

  mul_koeff_vec_ = std::max< std::int32_t > (0, mul_koeff_vec_);
}


template< class Archive >
void
EventBufsInfoVec2Image1::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoeventsobufoEventBufsInfo", super);
  arh& BOOST_SERIALIZATION_NVP (size_block_);
  arh& BOOST_SERIALIZATION_NVP (mul_koeff_vec_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const EventBufsInfoVec2Image1& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::helpers::casts::static_cast_helper< const ::libs::events::buf::EventBufsInfo& > (src));

  jvs = {
    { "parent", pjv },
    { "size_block", src.size_block_ },
    { "mul_koeff_vec", src.mul_koeff_vec_ }
  };
}


EventBufsInfoVec2Image1
tag_invoke (::boost::json::value_to_tag< EventBufsInfoVec2Image1 >, const ::boost::json::value& jvs)
{
  const auto&             pobj = jvs.at ("parent").as_object ();
  EventBufsInfoVec2Image1 ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufsInfo > (), pobj));
  // const ::boost::json::object& obj = jvs.as_object ();

  ret.size_block_    = ::libs::helpers::json::get_int32 (jvs.at ("size_block"));
  ret.mul_koeff_vec_ = ::libs::helpers::json::get_int32 (jvs.at ("mul_koeff_vec"));
  return ret;
}
}   // namespace libs::ievents::props::videos::generic::vec2image

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::vec2image::EventBufsInfoVec2Image1);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::vec2image::EventBufsInfoVec2Image1);
