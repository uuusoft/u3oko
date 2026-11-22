/**
\file       event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
*/
#include "events-base-includes_int.hpp"
#include "event.hpp"

namespace libs::events_base
{
using str2state_type = std::pair< std::string, ::libs::events::PropertyUsings >;

auto
str2event_state (const std::string& str) -> ::libs::events::PropertyUsings
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

  ::libs::utility::checks::throw_exception ("failed");
  return ::libs::events::PropertyUsings::disabled;
}


Event::Event (const Acessor& pha)
{
}


auto
Event::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return Event::gen_get_mid ();
}


auto
Event::get_genextprop_json () const -> const std::string&
{
  return genextprop_json_;
}


auto
Event::set_genextprop_json (const std::string& val) -> void
{
  genextprop_json_ = val;
}


auto
Event::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< Event > (this, deep);
}


void
Event::load_json_int (const ::boost::json::object& obj)
{
  if (!obj.try_at ("genextprop_json"))
  {
    return;
  }
  genextprop_json_ = ::libs::utility::json::get_string (obj.at ("genextprop_json"));
}


void
Event::save_json_int (::boost::json::object& obj) const
{
  obj["genextprop_json"] = ::libs::utility::json::to_string (genextprop_json_);
}


void
Event::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< Event > (src);
  super::copy_int (src);
  genextprop_json_ = dsrc->genextprop_json_;
}

#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
Event::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoeventsoIEvent", ::libs::events::IEvent);
  arh& BOOST_SERIALIZATION_NVP (genextprop_json_);
}
#endif
}   // namespace libs::events_base

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::Event);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::Event);
