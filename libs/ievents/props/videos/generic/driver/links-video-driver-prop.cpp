//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       links-video-driver-prop.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../../../includes_int.hpp"
#include "links-video-driver-prop.hpp"

namespace libs { namespace ievents { namespace props { namespace videos { namespace generics { namespace driver {

LinksVideoDriverProp::LinksVideoDriverProp (const Acessor& _ph) :
  pdriver2buff_ (nullptr),
  pdriver2mem_ (nullptr)
{
  property_name_ = gen_get_mid ();
}


LinksVideoDriverProp::~LinksVideoDriverProp ()
{}


::libs::events::IEvent::ptr
LinksVideoDriverProp::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<LinksVideoDriverProp> (this, _deep);
}


void
LinksVideoDriverProp::load_int (const base_functs::xml::itn& _prop)
{
  ::libs::ievents::Event::load_int (_prop);
#if 0
    base_functs::xml::ritn  _params = _prop->children ("param");
    base_functs::xml::itn _param  = _params.begin ();

    while ( _param != _params.end () )
    {

      pugi::xml_attribute _name_param = _param->attribute ("name");
      pugi::xml_attribute _val_param  = _param->attribute ("val");
      int         _ph_int   = 0;

      ++_param;
    }
#endif
  self_correct ();
  return;
}


void
LinksVideoDriverProp::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (LinksVideoDriverProp);
  super::copy_int (_src);
  pdriver2buff_ = _dsrc->pdriver2buff_;
  pdriver2mem_  = _dsrc->pdriver2mem_;
  return;
}


template <class Archive>
void
LinksVideoDriverProp::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  return;
}

}}}}}}      // namespace libs::ievents::props::videos::generics::driver

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generics::driver::LinksVideoDriverProp);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::videos::generics::driver::LinksVideoDriverProp);
