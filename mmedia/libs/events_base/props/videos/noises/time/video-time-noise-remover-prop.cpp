/**
\file       video-time-noise-remover-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
// #define U3_DBG_LOG_LEVEL_ENABLE
#include "../../../../events-base-includes_int.hpp"
#include "video-time-noise-remover-prop.hpp"

namespace libs::events_base::props::videos::noises::time
{
VideoTimeNoiseRemoverProp::VideoTimeNoiseRemoverProp (const Acessor& pha)
{
  bufs_.reserve (3);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::sat);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::hue);
}


auto
VideoTimeNoiseRemoverProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return VideoTimeNoiseRemoverProp::gen_get_mid ();
}


auto
VideoTimeNoiseRemoverProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< VideoTimeNoiseRemoverProp > (this, deep);
}


void
VideoTimeNoiseRemoverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  name_impl_          = obj.at ("name_impl").as_string ();
  bufs_               = ::boost::json::value_to< source_bufs_type > (obj.at (::libs::events::buf::consts::node_name));
  dump_frame_counter_ = ::libs::utility::json::get_uint32 (obj.at ("dump_counter_frame"));
}


void
VideoTimeNoiseRemoverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["name_impl"]                            = name_impl_;
  obj[::libs::events::buf::consts::node_name] = ::boost::json::value_from (bufs_);
  obj["dump_counter_frame"]                   = dump_frame_counter_;
}


void
VideoTimeNoiseRemoverProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoTimeNoiseRemoverProp > (src);
  super::copy_int (src);

  name_impl_          = dsrc->name_impl_;
  bufs_               = dsrc->bufs_;
  dump_frame_counter_ = dsrc->dump_frame_counter_;
}


void
VideoTimeNoiseRemoverProp::self_correct_int ()
{
}

#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
VideoTimeNoiseRemoverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (name_impl_);
  arh& BOOST_SERIALIZATION_NVP (bufs_);
  arh& BOOST_SERIALIZATION_NVP (dump_frame_counter_);
  // arh& BOOST_SERIALIZATION_NVP (indx_diff_buf_);
  // arh& BOOST_SERIALIZATION_NVP (impl_info_);

  self_correct ();
}
#endif
}   // namespace libs::events_base::props::videos::noises::time

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::noises::time::VideoTimeNoiseRemoverProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::noises::time::VideoTimeNoiseRemoverProp);
