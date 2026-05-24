/**
\file       event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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


Event::Event (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


Event::~Event ()
{
}


::libs::events::IEvent::ptr
Event::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< Event > (this, deep);
}


void
Event::load_json_int (const ::boost::json::object& obj)
{
  // super::load_json_int (obj);
}


void
Event::save_json_int (::boost::json::object& obj) const
{
  // super::save_json_int (obj);
}


void
Event::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (Event);
  super::copy_int (src);
}


template< class Archive >
void
Event::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoeventsoIEvent", ::libs::events::IEvent);
}
}   // namespace libs::ievents

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::Event);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::Event);
