/**
\file       video-space-noise-remover-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-space-noise-remover-prop.hpp"

namespace libs::ievents::props::videos::noises::space
{
VideoSpaceNoiseRemoverProp::VideoSpaceNoiseRemoverProp (const Acessor& ph) :
  name_impl_ ("default"),
  bufs_ ({ ::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::lit }),
  indx_cond_buf_ (::utils::dbufs::video::consts::offs::space_noise_filter_res),
  use_cond_buf_ (false),
  dump_counter_frame_ (0)
{
  property_name_ = gen_get_mid ();
}


VideoSpaceNoiseRemoverProp::~VideoSpaceNoiseRemoverProp ()
{
}


::libs::events::IEvent::ptr
VideoSpaceNoiseRemoverProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoSpaceNoiseRemoverProp > (this, deep);
}


void
VideoSpaceNoiseRemoverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  name_impl_          = obj.at ("name_impl").as_string ();
  bufs_               = ::boost::json::value_to< source_bufs_type > (obj.at ("evbufs"));
  indx_cond_buf_      = obj.at ("indx_cond_buf").as_string ();
  use_cond_buf_       = obj.at ("use_cond_buf").as_bool ();
  dump_counter_frame_ = ::libs::helpers::json::get_uint32 (obj.at ("dump_counter_frame"));

  const std::string impl_info_id = obj.at ("impl_info-id").is_string () ? obj.at ("impl_info-id").as_string ().c_str () : "";

  impl_info_ = ::libs::iproperties::helpers::get_pure_event_int (impl_info_id.c_str ());
  if (impl_info_)
  {
    impl_info_->load_json (obj.at ("impl_info").as_string ().c_str ());
  }
}


void
VideoSpaceNoiseRemoverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["name_impl"]          = name_impl_;
  obj["evbufs"]             = ::boost::json::value_from (bufs_);
  obj["indx_cond_buf"]      = indx_cond_buf_;
  obj["use_cond_buf"]       = use_cond_buf_;
  obj["dump_counter_frame"] = dump_counter_frame_;

  if (impl_info_)
  {
    obj["impl_info-id"] = impl_info_->get_mid ();
    obj["impl_info"]    = impl_info_->save_json ();
  }
}


void
VideoSpaceNoiseRemoverProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (VideoSpaceNoiseRemoverProp);
  super::copy_int (src);

  name_impl_          = dsrc->name_impl_;
  bufs_               = dsrc->bufs_;
  indx_cond_buf_      = dsrc->indx_cond_buf_;
  use_cond_buf_       = dsrc->use_cond_buf_;
  dump_counter_frame_ = dsrc->dump_counter_frame_;
  impl_info_          = ::libs::iproperties::helpers::clone_event (dsrc->impl_info_.get ());
}


void
VideoSpaceNoiseRemoverProp::self_correct_int ()
{
}


template< class Archive >
void
VideoSpaceNoiseRemoverProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  ar& BOOST_SERIALIZATION_NVP (name_impl_);
  ar& BOOST_SERIALIZATION_NVP (bufs_);
  ar& BOOST_SERIALIZATION_NVP (dump_counter_frame_);
  ar& BOOST_SERIALIZATION_NVP (indx_cond_buf_);
  ar& BOOST_SERIALIZATION_NVP (impl_info_);
  ar& BOOST_SERIALIZATION_NVP (use_cond_buf_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::noises::space

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
