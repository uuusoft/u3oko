//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       property-storage-module-event.cpp
\date       22.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../includes_int.hpp"
#include "property-storage-module-event.hpp"

namespace libs { namespace ievents { namespace props { namespace modules { namespace storage {

PropertyStorageModuleEvent::PropertyStorageModuleEvent (const Acessor& _ph) :
  check_ (CheckerStorageType::start_stop)
{
  property_name_ = gen_get_mid ();
}


PropertyStorageModuleEvent::~PropertyStorageModuleEvent ()
{}


const PropertyStorageModuleEvent::paths_type&
PropertyStorageModuleEvent::get_paths () const
{
  return paths_;
}


const CheckerStorageType&
PropertyStorageModuleEvent::get_check () const
{
  return check_;
}


::libs::events::IEvent::ptr
PropertyStorageModuleEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<PropertyStorageModuleEvent> (this, _deep);
}


void
PropertyStorageModuleEvent::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      ::libs::icore::xml::helpers::load (_param, "checker", [this](const std::string& _val) {
        check_ = str2checker_storage (_val);
        return;
      });

      const std::string _name_param = _param->attribute ("name").as_string ();
      if (std::string ("path_info") == _name_param)
        {
          paths_.push_back (PathInfo ());
          paths_.back ().load (_param);
        }

      ++_param;
    }
  return;
}


void
PropertyStorageModuleEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (PropertyStorageModuleEvent);
  super::copy_int (_src);
  paths_ = _dsrc->paths_;
  check_ = _dsrc->check_;
  return;
}


template <class Archive>
void
PropertyStorageModuleEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (paths_);
  ar& BOOST_SERIALIZATION_NVP (check_);
  return;
}

}}}}}      // namespace libs::ievents::props::modules::storage

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::modules::storage::PropertyStorageModuleEvent);
