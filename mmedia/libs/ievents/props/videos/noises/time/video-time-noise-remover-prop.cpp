/**
\file       video-time-noise-remover-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-time-noise-remover-prop.hpp"

namespace libs::ievents::props::videos::noises::time
{
VideoTimeNoiseRemoverProp::VideoTimeNoiseRemoverProp (const Acessor& ph) :
  name_impl_ ("median2"),
  bufs_ ({ utils::dbufs::video::consts::offs::lit, utils::dbufs::video::consts::offs::sat, utils::dbufs::video::consts::offs::hue }),
  dump_counter_frame_ (0),
  indx_diff_buf_ (utils::dbufs::video::consts::offs::move_detect_res)
{
  property_name_ = gen_get_mid ();
}


VideoTimeNoiseRemoverProp::~VideoTimeNoiseRemoverProp ()
{
}


::libs::events::IEvent::ptr
VideoTimeNoiseRemoverProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoTimeNoiseRemoverProp > (this, deep);
}


void
VideoTimeNoiseRemoverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  name_impl_          = obj.at ("name_impl").as_string ();
  bufs_               = ::boost::json::value_to< source_bufs_type > (obj.at ("evbufs"));
  indx_diff_buf_      = obj.at ("indx_diff_buf").as_string ();
  dump_counter_frame_ = ::libs::helpers::json::get_uint32 (obj.at ("dump_counter_frame"));

  const std::string impl_info_id = obj.at ("impl_info-id").is_string () ? obj.at ("impl_info-id").as_string ().c_str () : "";

  impl_info_ = ::libs::iproperties::helpers::get_pure_event_int (impl_info_id.c_str ());
  if (impl_info_)
  {
    impl_info_->load_json (obj.at ("impl_info").as_string ().c_str ());
  }
}


void
VideoTimeNoiseRemoverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["name_impl"]          = name_impl_;
  obj["evbufs"]             = ::boost::json::value_from (bufs_);
  obj["indx_diff_buf"]      = indx_diff_buf_;
  obj["dump_counter_frame"] = dump_counter_frame_;

  if (impl_info_)
  {
    obj["impl_info-id"] = impl_info_->get_mid ();
    obj["impl_info"]    = impl_info_->save_json ();
  }
}


void
VideoTimeNoiseRemoverProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (VideoTimeNoiseRemoverProp);
  super::copy_int (src);
  name_impl_          = dsrc->name_impl_;
  bufs_               = dsrc->bufs_;
  dump_counter_frame_ = dsrc->dump_counter_frame_;
  indx_diff_buf_      = dsrc->indx_diff_buf_;
  impl_info_          = ::libs::iproperties::helpers::clone_event (dsrc->impl_info_.get ());
}


void
VideoTimeNoiseRemoverProp::self_correct_int ()
{
}


template< class Archive >
void
VideoTimeNoiseRemoverProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  ar& BOOST_SERIALIZATION_NVP (name_impl_);
  ar& BOOST_SERIALIZATION_NVP (bufs_);
  ar& BOOST_SERIALIZATION_NVP (dump_counter_frame_);
  ar& BOOST_SERIALIZATION_NVP (indx_diff_buf_);
  ar& BOOST_SERIALIZATION_NVP (impl_info_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::noises::time

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp);
