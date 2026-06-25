/**
\file       video-space-noise-remover-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-space-noise-remover-prop.hpp"

namespace libs::ievents::props::videos::noises::space
{
VideoSpaceNoiseRemoverProp::VideoSpaceNoiseRemoverProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();

  bufs_.reserve (3);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::sat);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::hue);
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

  name_impl_ = obj.at ("name_impl").as_string ();
  bufs_      = ::boost::json::value_to< source_bufs_type > (obj.at ("evbufs"));
}


void
VideoSpaceNoiseRemoverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["name_impl"] = name_impl_;
  obj["evbufs"]    = ::boost::json::value_from (bufs_);
}


void
VideoSpaceNoiseRemoverProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoSpaceNoiseRemoverProp > (src);
  super::copy_int (src);

  name_impl_ = dsrc->name_impl_;
  bufs_      = dsrc->bufs_;
}


void
VideoSpaceNoiseRemoverProp::self_correct_int ()
{
}


template< class Archive >
void
VideoSpaceNoiseRemoverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);

  arh& BOOST_SERIALIZATION_NVP (name_impl_);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::noises::space

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp);
