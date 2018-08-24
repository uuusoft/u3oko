//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       end-point-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "end-point-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace terminals {

EndPointProp::EndPointProp (const Acessor& _ph) :
  enable_send_ (true),
  enable_notify_ (false)
//id_ (0),
//http_buffs_ (utils::dbuffs::video::consts::offs::mjpg, utils::dbuffs::video::consts::offs::invalid)
{
  property_name_ = gen_get_type_text_id ();
}


EndPointProp::~EndPointProp ()
{}


::libs::events::IEvent::ptr
EndPointProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<EndPointProp> (this, _deep);
}


void
EndPointProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      ::libs::icore::xml::helpers::load<bool> (_param, "send", enable_send_);
      ::libs::icore::xml::helpers::load<bool> (_param, "notify", enable_notify_);
      //::libs::icore::xml::helpers::load<int> (_param, "id", id_);

      const std::string _name_param = _param->attribute ("name").as_string ();
      /*
      if (std::string ("gui_buffs") == _name_param)
        {
          gui_buffs_.load (_param);
          gui_buffs_.check (true, false);
        }
      else if (std::string ("http_buffs") == _name_param)
        {
          http_buffs_.load (_param);
          http_buffs_.check (true, false);
        }
        */
      ++_param;
    }

  self_correct ();
  return;
}

#if 0
int
EndPointProp::get_id () const
{
  return id_;
}
#endif

bool
EndPointProp::is_send () const
{
  return enable_send_;
}


bool
EndPointProp::is_notify () const
{
  return enable_notify_;
}

#if 0
const BuffEventInfo&
EndPointProp::get_gui_buffs () const
{
  return gui_buffs_;
}


const BuffEventInfo&
EndPointProp::get_http_buffs () const
{
  return http_buffs_;
}
#endif

void
EndPointProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (EndPointProp);
  super::copy_int (_src);
  enable_send_   = _dsrc->enable_send_;
  enable_notify_ = _dsrc->enable_notify_;
  //id_            = _dsrc->id_;
  //gui_buffs_     = _dsrc->gui_buffs_;
  //http_buffs_    = _dsrc->http_buffs_;
  return;
}


template <class Archive>
void
EndPointProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (enable_send_);
  ar& BOOST_SERIALIZATION_NVP (enable_notify_);
  //ar& BOOST_SERIALIZATION_NVP (id_);
  //ar& BOOST_SERIALIZATION_NVP (gui_buffs_);
  //ar& BOOST_SERIALIZATION_NVP (http_buffs_);
  return;
}

}}}}      // namespace libs::ievents::props::terminals

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::terminals::EndPointProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::terminals::EndPointProp);
