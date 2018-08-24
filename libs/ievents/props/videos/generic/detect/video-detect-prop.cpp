//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       video-detect-prop.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "video-detect-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace detect {

VideoDetectProp::VideoDetectProp (const Acessor& _ph) :
  mode_ ("default"),
  time_id_ (::libs::helpers::consts::iinvalid),
  zone_id_ (::libs::helpers::consts::iinvalid),
  bound_ (1),
  time_ (30),
  lazy_optim_ (true)
{
  property_name_ = gen_get_type_text_id ();
}


VideoDetectProp::~VideoDetectProp ()
{}


::libs::events::IEvent::ptr
VideoDetectProp::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<VideoDetectProp> (this, _deep);
}


void
VideoDetectProp::load_int (const base_functs::xml::itn& _prop)
{
  super::load_int (_prop);

  {
    base_functs::xml::ritn _params = _prop->children ("param");
    base_functs::xml::itn  _param  = _params.begin ();

    while (_param != _params.end ())
      {
        ::libs::icore::xml::helpers::load<bool> (_param, "lazy_optim", lazy_optim_);
        ::libs::icore::xml::helpers::load<int> (_param, "time_id", time_id_);
        ::libs::icore::xml::helpers::load<int> (_param, "zone_id", zone_id_);
        ::libs::icore::xml::helpers::load<std::string> (_param, "mode", mode_);
        ::libs::icore::xml::helpers::load<int> (_param, "bound", bound_);
        ::libs::icore::xml::helpers::load<int> (_param, "time", time_);

        ::libs::helpers::utils::check_bound<int> (time_, 15, 60);

        ++_param;
      }
  }

  {
    base_functs::xml::ritn _params = _prop->children (::libs::events::buff::consts::node_name.c_str ());
    base_functs::xml::itn  _param  = _params.begin ();

    while (_param != _params.end ())
      {
        buff_.load (_param);
        buff_.check (true, false);
        ++_param;
      }
  }

  self_correct ();
  return;
}


void
VideoDetectProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (VideoDetectProp);
  super::copy_int (_src);
  time_id_    = _dsrc->time_id_;
  mode_       = _dsrc->mode_;
  zone_id_    = _dsrc->zone_id_;
  bound_      = _dsrc->bound_;
  buff_       = _dsrc->buff_;
  time_       = _dsrc->time_;
  lazy_optim_ = _dsrc->lazy_optim_;
  return;
}


template <class Archive>
void
VideoDetectProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);

  ar& BOOST_SERIALIZATION_NVP (time_id_);
  ar& BOOST_SERIALIZATION_NVP (mode_);
  ar& BOOST_SERIALIZATION_NVP (zone_id_);
  ar& BOOST_SERIALIZATION_NVP (bound_);
  ar& BOOST_SERIALIZATION_NVP (buff_);
  ar& BOOST_SERIALIZATION_NVP (time_);
  ar& BOOST_SERIALIZATION_NVP (lazy_optim_);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::detect

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::detect::VideoDetectProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::detect::VideoDetectProp);
