/**
\file       freq-video-noise-remover-prop.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "freq-video-noise-remover-prop.hpp"

namespace libs::events_base::props::videos::noises::freq
{
FreqVideoNoiseRemoverProp::FreqVideoNoiseRemoverProp (const Acessor& pha) :
  bufs_ ({ { syn::offs::lit, InfoBuffFreqNoiseRemover (syn::offs::lit, syn::offs::lit, syn::offs::lit, 8, 1) },
           { syn::offs::hue, InfoBuffFreqNoiseRemover (syn::offs::hue, syn::offs::hue, syn::offs::hue, 8, 1) },
           { syn::offs::hue, InfoBuffFreqNoiseRemover (syn::offs::sat, syn::offs::sat, syn::offs::sat, 8, 1) } })
{
}


auto
FreqVideoNoiseRemoverProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return FreqVideoNoiseRemoverProp::gen_get_mid ();
}


auto
FreqVideoNoiseRemoverProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
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
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< FreqVideoNoiseRemoverProp > (src);
  super::copy_int (src);
  bufs_ = dsrc->bufs_;
}


template< class Archive >
void
FreqVideoNoiseRemoverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (bufs_);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::noises::freq

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::noises::freq::FreqVideoNoiseRemoverProp);
