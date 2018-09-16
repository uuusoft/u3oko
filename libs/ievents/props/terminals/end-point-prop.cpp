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
{
  property_name_ = gen_get_mid ();
}


EndPointProp::~EndPointProp ()
{}


::libs::events::IEvent::ptr
EndPointProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
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

      const std::string _name_param = _param->attribute ("name").as_string ();
      ++_param;
    }

  self_correct ();
  return;
}

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


void
EndPointProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (EndPointProp);
  super::copy_int (_src);
  enable_send_   = _dsrc->enable_send_;
  enable_notify_ = _dsrc->enable_notify_;
  return;
}


template <class Archive>
void
EndPointProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (enable_send_);
  ar& BOOST_SERIALIZATION_NVP (enable_notify_);
  return;
}

}}}}      // namespace libs::ievents::props::terminals

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::terminals::EndPointProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::terminals::EndPointProp);
