/**
\file       event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "event.hpp"

namespace libs::ievents
{
using str2state_type = std::pair< std::string, ::libs::events::PropertyUsings >;

::libs::events::PropertyUsings
str2event_state (const std::string& str)
{
  static const str2state_type vals[] = {
    str2state_type ("0", ::libs::events::PropertyUsings::disabled),
    str2state_type ("disable", ::libs::events::PropertyUsings::disabled),
    str2state_type ("1", ::libs::events::PropertyUsings::enabled),
    str2state_type ("enable", ::libs::events::PropertyUsings::enabled),
    str2state_type ("-", ::libs::events::PropertyUsings::automatic),
    str2state_type ("auto", ::libs::events::PropertyUsings::automatic)
  };

  for (const auto& val : vals)
  {
    if (val.first == str)
    {
      return val.second;
    }
  }

  U3_ASSERT_SIGNAL ("failed");
  return ::libs::events::PropertyUsings::disabled;
}


Event::Event (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


auto
Event::get_gextp_json () const -> const std::string&
{
  return gextp_json_;
}


auto
Event::set_gextp_json (const std::string& val) -> void
{
  gextp_json_ = val;
}


::libs::events::IEvent::ptr
Event::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< Event > (this, deep);
}


void
Event::load_json_int (const ::boost::json::object& obj)
{
  U3_XLOG_DBG ("Event::load_json_int::---->" + TOLOG (boost::json::serialize (obj)));
  // gextp_json_ = ::libs::helpers::json::get_string (obj.at ("gextp_json"));
  U3_XLOG_DBG ("Event::load_json_int::<----");
}


void
Event::save_json_int (::boost::json::object& obj) const
{
  U3_XLOG_DBG ("Event::save_json_int::---->" + TOLOG (boost::json::serialize (obj)));
  // obj["gextp_json"] = ::libs::helpers::json::to_string (gextp_json_);
  U3_XLOG_DBG ("Event::save_json_int::<----");
}


void
Event::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< Event > (src);
  super::copy_int (src);
  gextp_json_ = dsrc->gextp_json_;
}


template< class Archive >
void
Event::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoeventsoIEvent", ::libs::events::IEvent);
  arh& BOOST_SERIALIZATION_NVP (gextp_json_);
}
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::Event);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::Event);
