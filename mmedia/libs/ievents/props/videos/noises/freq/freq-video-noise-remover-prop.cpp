/**
\file       freq-video-noise-remover-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "freq-video-noise-remover-prop.hpp"

namespace libs::ievents::props::videos::noises::freq
{
FreqVideoNoiseRemoverProp::FreqVideoNoiseRemoverProp (const Acessor& ph) :
  bufs_ ({ { ::utils::dbufs::video::consts::offs::lit, InfoBuffFreqNoiseRemover (::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit, ::utils::dbufs::video::consts::offs::lit, 8, 1) },
           { ::utils::dbufs::video::consts::offs::hue, InfoBuffFreqNoiseRemover (::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::hue, ::utils::dbufs::video::consts::offs::hue, 8, 1) },
           { ::utils::dbufs::video::consts::offs::hue, InfoBuffFreqNoiseRemover (::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::sat, ::utils::dbufs::video::consts::offs::sat, 8, 1) } })
{
  property_name_ = gen_get_mid ();
}


FreqVideoNoiseRemoverProp::~FreqVideoNoiseRemoverProp ()
{
}


::libs::events::IEvent::ptr
FreqVideoNoiseRemoverProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< FreqVideoNoiseRemoverProp > (this, deep);
}


void
FreqVideoNoiseRemoverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  bufs_ = ::boost::json::value_to< freq_bufs_type > (obj.at ("evbufs"));
}


void
FreqVideoNoiseRemoverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["evbufs"] = ::boost::json::value_from (bufs_);
}


void
FreqVideoNoiseRemoverProp::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (FreqVideoNoiseRemoverProp);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
FreqVideoNoiseRemoverProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::ievents::props::videos::noises::freq

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
