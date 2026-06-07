/**
\file       events-buf-info.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "events-buf-info-motion-est.hpp"

namespace libs::ievents::props::videos::generic::motion_est
{
EventBufsInfoMotionEst::EventBufsInfoMotionEst (
  const ::utils::dbufs::video::consts::offs::off_buf_type& src,
  const ::utils::dbufs::video::consts::offs::off_buf_type& dst,
  const Acessor&) :
  ::libs::events::buf::EventBufsInfo (src, dst),
  max_error_ (16.0F * 16.0F * 10.0F),
  min_error_ (0.0F),
  size_block_ (16),
  size_search_ (16)
{
}


EventBufsInfoMotionEst::EventBufsInfoMotionEst (const ::libs::events::buf::EventBufsInfo& buf) :
  ::libs::events::buf::EventBufsInfo (buf)
{
}


void
EventBufsInfoMotionEst::check_int ()
{
  U3_CHECK (min_error_ >= 0.0F, "min large 0");
  U3_CHECK (max_error_ > 0.0F, "max less 0");
  U3_CHECK (min_error_ < max_error_, "min large max");
  U3_CHECK (8 == size_block_ || 16 == size_block_ || 32 == size_block_, "invalid blok size");
  U3_CHECK (size_search_ > 0, "size search less 0");
  U3_CHECK (size_search_ <= 126, "size search large 126");   // 127 reserved for invalid
}


void
EventBufsInfoMotionEst::correct_int ()
{
  min_error_   = std::max (0.0F, min_error_);
  max_error_   = std::max (0.001f, max_error_);
  max_error_   = std::max (min_error_ + 0.001f, max_error_);
  size_search_ = std::max< std::int16_t > (1, size_search_);
  size_search_ = std::min< std::int16_t > (126, size_search_);

  if (size_block_ != 8 && size_block_ != 16 && size_block_ != 32)
  {
    size_block_ = 8;
  }
}


template< class Archive >
void
EventBufsInfoMotionEst::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoeventsobufoEventBufsInfoMotionEst", super);
  arh& BOOST_SERIALIZATION_NVP (max_error_);
  arh& BOOST_SERIALIZATION_NVP (min_error_);
  arh& BOOST_SERIALIZATION_NVP (size_block_);
  arh& BOOST_SERIALIZATION_NVP (size_search_);
  arh& BOOST_SERIALIZATION_NVP (search_vecs_);
}


void
tag_invoke (::boost::json::value_from_tag tag, ::boost::json::value& jvs, const EventBufsInfoMotionEst& src)
{
  ::boost::json::value pjv;
  ::libs::events::buf::tag_invoke (
    tag,
    pjv,
    ::libs::helpers::casts::static_cast_helper< const ::libs::events::buf::EventBufsInfo& > (src));

  // EAI-JSON-TEST-86
  jvs = {
    { "parent", pjv },
    { "max_error", src.max_error_ },
    { "min_error", src.min_error_ },
    { "size_block", src.size_block_ },
    { "size_search", src.size_search_ },
    { "search_vecs", ::boost::json::value_from (src.search_vecs_) }
  };
}


EventBufsInfoMotionEst
tag_invoke (::boost::json::value_to_tag< EventBufsInfoMotionEst >, const ::boost::json::value& jvs)
{
  const auto&                  pobj = jvs.at ("parent").as_object ();
  EventBufsInfoMotionEst       ret (::libs::events::buf::tag_invoke (::boost::json::value_to_tag< ::libs::events::buf::EventBufsInfo > (), pobj));
  const ::boost::json::object& obj = jvs.as_object ();

  ret.max_error_   = ::libs::helpers::json::get_float (obj.at ("max_error"));
  ret.min_error_   = ::libs::helpers::json::get_float (obj.at ("min_error"));
  ret.size_block_  = ::libs::helpers::json::get_int32 (obj.at ("size_block"));
  ret.size_search_ = ::libs::helpers::json::get_int32 (obj.at ("size_search"));
  ret.search_vecs_ = ::boost::json::value_to< EventBufsInfoMotionEst::vectors_type > (obj.at ("search_vecs"));
  return ret;
}
}   // namespace libs::ievents::props::videos::generic::motion_est

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::motion_est::EventBufsInfoMotionEst);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::motion_est::EventBufsInfoMotionEst);
