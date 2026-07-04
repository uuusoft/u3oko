/**
\file       links-video-driver-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "links-video-driver-prop.hpp"

namespace libs::events_base::props::videos::generic::driver
{
LinksVideoDriverProp::LinksVideoDriverProp (const Acessor& pha)
{
}


auto
LinksVideoDriverProp::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return LinksVideoDriverProp::gen_get_mid ();
}


auto
LinksVideoDriverProp::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< LinksVideoDriverProp > (this, deep);
}


void
LinksVideoDriverProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  U3_ASSERT_NT (0, "LinksVideoDriverProp::load_json_int:: wtf???");
}


void
LinksVideoDriverProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  U3_ASSERT_NT (0, "LinksVideoDriverProp::save_json_int:: wtf???");
}


void
LinksVideoDriverProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< LinksVideoDriverProp > (src);
  super::copy_int (src);

  pdriver2buf_ = dsrc->pdriver2buf_;
  pdriver2mem_ = dsrc->pdriver2mem_;
}


template< class Archive >
void
LinksVideoDriverProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);

  self_correct ();
}
}   // namespace libs::events_base::props::videos::generic::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::driver::LinksVideoDriverProp);
