/**
\file       ievent.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    mevents
*/
// #define U3_USE_DBG_LOG_LEVEL_FOR_THIS_UNITE
#include "includes_int.hpp"
#include "ievent.hpp"

namespace libs::events
{
IEvent::IEvent ()
{
}


auto
IEvent::get_mid () const -> const IEvent::hid_type&
{
  return get_mid_int ();
}


auto
IEvent::clone (const ::libs::events::Deeps& deep) const -> IEvent::ptr
{
  return clone_int (deep);
}


void
IEvent::copy (const IEvent::craw_ptr src)
{
  copy_int (src);
  self_correct ();
}

#if 0
auto
IEvent::get_mid () const -> IEvent::hid_type
{
  U3_ASSERT (!property_name_.empty ());
  return property_name_;
}
#endif

auto
IEvent::get_using_state () const -> const PropertyUsings&
{
  return state_;
}


void
IEvent::load_json (const std::string& prop)
{
  U3_XLOG_DBG ("IEvent::load_json::---->")
  ::boost::json::parse_options opt;

  opt.allow_comments        = true;
  opt.allow_trailing_commas = true;
  opt.allow_invalid_utf8    = true;
  opt.allow_invalid_utf16   = true;
  // opt.allow_infinity_and_nan = false;

  auto pr   = ::boost::json::parse (prop, {}, opt);
  auto kind = pr.kind ();
  if (::boost::json::kind::object != kind)
  {
    U3_XLOG_ERROR ("::boost::json::kind::object != kind");
    return;
  }

  const ::boost::json::object& obj = pr.get_object ();
  if (obj.empty ())
  {
    U3_XLOG_ERROR ("кусшму obj.empty from prop");
    return;
  }

  state_ = ::libs::utility::casts::static_cast_helper< PropertyUsings > (::libs::utility::json::get_uint32 (obj.at ("libs_events_ievent_state")));
  // property_name_ = obj.at ("libs_events_property_name").as_string ();

  load_json_int (obj);
  self_correct ();
  U3_XLOG_DBG ("IEvent::load_json::<----")
}


auto
IEvent::save_json () const -> std::string
{
  ::boost::json::object val;

  val["libs_events_ievent_state"]  = U3_CAST_UINT32_FORCE (state_);
  val["libs_events_property_name"] = gen_get_mid ();
  // val["libs_events_property_name"] = property_name_;

  save_json_int (val);
  const auto ret = ::boost::json::serialize (val);
  return ret;
}


void
IEvent::copy_int (const IEvent::craw_ptr src)
{
  // IEvent::operator= (*src);
  // property_name_ = src->property_name_;
  state_ = src->state_;
}


void
IEvent::self_correct ()
{
  self_correct_int ();
}


void
IEvent::self_correct_int ()
{
}


void
IEvent::sync_txt2val ()
{
  sync_txt2val_int ();
}


void
IEvent::sync_txt2val_int ()
{
}


void
IEvent::sync_val2txt ()
{
  sync_val2txt_int ();
}


void
IEvent::sync_val2txt_int ()
{
}


auto
IEvent::is_failed_int () const -> bool
{
  return false;
}


template< class Archive >
void
IEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  // arh& BOOST_SERIALIZATION_NVP (property_name_);
  arh& BOOST_SERIALIZATION_NVP (state_);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::IEvent);
