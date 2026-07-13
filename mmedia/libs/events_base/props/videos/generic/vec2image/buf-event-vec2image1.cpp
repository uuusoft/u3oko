/**
\file       buf-event-vec2image1.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "../../../../events-base-includes_int.hpp"
#include "buf-event-vec2image1.hpp"

namespace libs::events_base::props::videos::generic::vec2image
{
EventBufsVec2Image1::EventBufsVec2Image1 (
  const ::utils::dbufs::video::consts::offs::off_buf_type& src,
  const ::utils::dbufs::video::consts::offs::off_buf_type& dst) :

  ::libs::events::buf::EventBufs (src, dst),
  size_block_ (16),
  mul_koeff_vec_ (1)
{
}


EventBufsVec2Image1::EventBufsVec2Image1 (const ::libs::events::buf::EventBufs& buf) :
  ::libs::events::buf::EventBufs (buf),
  size_block_ (16),
  mul_koeff_vec_ (1)
{
}


void
EventBufsVec2Image1::check_int ()
{
  U3_CHECK (8 == size_block_ || 16 == size_block_ || 32 == size_block_, "size block invalid");
  U3_CHECK (mul_koeff_vec_ > 0, "mul koeff less 0");
}


void
EventBufsVec2Image1::correct_int ()
{
  if (size_block_ != 8 && size_block_ != 16 && size_block_ != 32)
  {
    size_block_ = 8;
  }

  mul_koeff_vec_ = std::max< std::int32_t > (0, mul_koeff_vec_);
}


template< class Archive >
void
EventBufsVec2Image1::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoeventsobufoEventBufs", super);
  arh& BOOST_SERIALIZATION_NVP (size_block_);
  arh& BOOST_SERIALIZATION_NVP (mul_koeff_vec_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const EventBufsVec2Image1& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::utility::casts::static_cast_helper< const ::libs::events::buf::EventBufs& > (src));

  jvs = {
    { "parent", pjv },
    { "size_block", src.size_block_ },
    { "mul_koeff_vec", src.mul_koeff_vec_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< EventBufsVec2Image1 >, const ::boost::json::value& jvs) -> EventBufsVec2Image1
{
  const auto&         pobj = jvs.at ("parent").as_object ();
  EventBufsVec2Image1 ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufs > (), pobj));
  // const ::boost::json::object& obj = jvs.as_object ();

  ret.size_block_    = ::libs::utility::json::get_int32 (jvs.at ("size_block"));
  ret.mul_koeff_vec_ = ::libs::utility::json::get_int32 (jvs.at ("mul_koeff_vec"));
  return ret;
}
}   // namespace libs::events_base::props::videos::generic::vec2image

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::vec2image::EventBufsVec2Image1);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::vec2image::EventBufsVec2Image1);
