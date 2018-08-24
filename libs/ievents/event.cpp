//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "event.hpp"

namespace libs { namespace ievents {

using str2state_type = std::pair<std::string, UsingStateEvent>;

UsingStateEvent
str2event_state (const std::string& _str)
{
  static const str2state_type _vals[] = {
    str2state_type ("0", UsingStateEvent::disabled),
    str2state_type ("disable", UsingStateEvent::disabled),
    str2state_type ("1", UsingStateEvent::enabled),
    str2state_type ("enable", UsingStateEvent::enabled),
    str2state_type ("-", UsingStateEvent::automatic),
    str2state_type ("auto", UsingStateEvent::automatic)
  };

  for (const auto& _val : _vals)
    {
      if (_val.first == _str)
        {
          return _val.second;
        }
    }

  UASSERT_SIGNAL ("failed");
  return UsingStateEvent::disabled;
}


Event::Event (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


Event::~Event ()
{}


::libs::events::IEvent::ptr
Event::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<Event> (this, _deep);
}


void
Event::load_int (const base_functs::xml::itn& _prop)
{
  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");
      std::string         _str;

      if (::libs::icore::xml::helpers::load<std::string> (_param, "active", _str))
        {
          state_ = str2event_state (_str);
        }

      ++_param;
    }

  self_correct ();
  return;
}


bool
Event::check_node_int (const base_functs::xml::itn& _node)
{
  //  дополнительной проверки (кроме совпадения имени свойства) в большинстве случаев не требуется.
  return true;
}


void
Event::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (Event);
  super::copy_int (_src);
  return;
}


template <class Archive>
void
Event::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}      // namespace libs::ievents

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::Event);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::Event);
