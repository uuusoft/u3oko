/**
\file       ievent.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    mevents
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "ievent.hpp"

namespace libs::events
{
IEvent::IEvent ()
{
  property_name_ = gen_get_mid ();
}


IEvent::ptr
IEvent::clone (const ::libs::events::Deeps& deep) const
{
  return clone_int (deep);
}


void
IEvent::copy (const IEvent::craw_ptr src)
{
  copy_int (src);
  self_correct ();
}


const IEvent::hid_type&
IEvent::get_mid () const
{
  U3_ASSERT (!property_name_.empty ());
  return property_name_;
}


const PropertyUsings&
IEvent::get_using_state () const
{
  return state_;
}


void
IEvent::load_json (const std::string& prop)
{
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
    U3_XLOG_ERROR ("obj.empty ()");
    return;
  }

  state_         = ::libs::helpers::casts::static_cast_helper< PropertyUsings > (::libs::helpers::json::get_uint32 (obj.at ("libs_events_ievent_state")));
  property_name_ = obj.at ("libs_events_property_name").as_string ();

  load_json_int (obj);
  self_correct ();
}


std::string
IEvent::save_json () const
{
  ::boost::json::object val;

  val["libs_events_ievent_state"]  = U3_CAST_UINT32_FORCE (state_);
  val["libs_events_property_name"] = property_name_;

  save_json_int (val);
  const auto ret = ::boost::json::serialize (val);
  return ret;
}


void
IEvent::copy_int (const IEvent::craw_ptr src)
{
  // IEvent::operator= (*src);
  property_name_ = src->property_name_;
  state_         = src->state_;
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


bool
IEvent::is_failed_int () const
{
  return false;
}


template< class Archive >
void
IEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (property_name_);
  arh& BOOST_SERIALIZATION_NVP (state_);
}
}   // namespace libs::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::IEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::events::IEvent);
