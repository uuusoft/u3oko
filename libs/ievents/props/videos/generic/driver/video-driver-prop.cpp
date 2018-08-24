//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-driver-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-driver-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {

VideoDriverProp::VideoDriverProp (const Acessor& _ph) :
  indx_device_ (0),
  cat_dshow_ (::libs::helpers::uids::cat::cat_video_device)
{
  property_name_ = gen_get_type_text_id ();
  sync_data ();
}


VideoDriverProp::~VideoDriverProp ()
{}


::libs::events::IEvent::ptr
VideoDriverProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoDriverProp> (this, _deep);
}


void
VideoDriverProp::load_int (const base_functs::xml::itn& _prop)
{
  ::libs::ievents::Event::load_int (_prop);

  base_functs::xml::ritn _params = _prop->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");

      ::libs::icore::xml::helpers::load<std::string> (_param, "type", name_impl_dll_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "text", text_);
      ::libs::icore::xml::helpers::load<std::string> (_param, "name", name_);
      ::libs::icore::xml::helpers::load<int> (_param, "indx_device", indx_device_);

      ++_param;
    }

  sync_data ();
  self_correct ();
  return;
}

void
VideoDriverProp::sync_data ()
{
  if (name_impl_dll_.empty ())
    {
#if defined(UUU_OS_WIN32_DESKTOP)
      name_impl_dll_ = "vss_windows_dshow_vgen";
#elif defined(UUU_OS_ANDROID)
      name_impl_dll_ = "vss_android_java_vgen";
      //name_impl_dll_ = "vss_android_openmax_vgen";
#elif defined(UUU_OS_GNU_LINUX)
      name_impl_dll_ = "vss_fake_vgen";
#elif defined(UUU_OS_RASPBERRY)
      name_impl_dll_ = "vss_raspberry_openmax_vgen";
#else
#error select OS
#endif
    }
  return;
}


void
VideoDriverProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoDriverProp);
  super::copy_int (_src);
  name_impl_dll_ = _dsrc->name_impl_dll_;
  text_          = _dsrc->text_;
  name_          = _dsrc->name_;
  indx_device_   = _dsrc->indx_device_;
  return;
}


template <class Archive>
void
VideoDriverProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (name_impl_dll_);
  ar& BOOST_SERIALIZATION_NVP (text_);
  ar& BOOST_SERIALIZATION_NVP (name_);
  ar& BOOST_SERIALIZATION_NVP (indx_device_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::driver::VideoDriverProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::driver::VideoDriverProp);
