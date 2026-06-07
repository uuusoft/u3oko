/**
\file       video-convolution-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-convolution-prop.hpp"

namespace libs::ievents::props::videos::generic::convolution
{
VideoConvolutionProp::VideoConvolutionProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();

  bufs_.reserve (3);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::sat);
  bufs_.emplace_back (::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::hue);
  // bufs_.emplace_back (BuffVideoConvolutionProp (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit));
  // bufs_.emplace_back (BuffVideoConvolutionProp (::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::sat));
  // bufs_.emplace_back (BuffVideoConvolutionProp (::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::hue));
}


::libs::events::IEvent::ptr
VideoConvolutionProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< VideoConvolutionProp > (this, deep);
}


void
VideoConvolutionProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  bufs_ = ::boost::json::value_to< std::vector< BuffVideoConvolutionProp > > (obj.at ("evbufs"));
}


void
VideoConvolutionProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  obj["evbufs"] = ::boost::json::value_from (bufs_);
}


void
VideoConvolutionProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< VideoConvolutionProp > (src);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
VideoConvolutionProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::generic::convolution

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::convolution::VideoConvolutionProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::convolution::VideoConvolutionProp);
