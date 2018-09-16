//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       events-impl.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       21.07.2017
\copyright  www.uuusoft.com
\project    uuu_devents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "events-impl.hpp"

namespace dlls { namespace devents { namespace impl {

EventsImpl::EventsImpl ()
{
  guard_type _grd (mtx_);
  construct ();
}


EventsImpl::~EventsImpl ()
{}


IEvent::ptr
EventsImpl::get (const hid_type& _id)
{
  guard_type _grd (mtx_);
  auto       _itf = gen_funct_events_.find (_id);

  if (gen_funct_events_.end () == _itf)
    {
      XULOG_ERROR ("function for create id event not found, " << _id);
      return IEvent::ptr ();
    }

  auto _ret = _itf->second ();
  UASSERT (_ret);
  return _ret;
}


IEvent::ptr
EventsImpl::clone (const IEvent::craw_ptr _src, const ::libs::events::DeepEventCloneType& _type)
{
  return _src->clone (_type);
}


void*
EventsImpl::dcast (IEvent::craw_ptr _src, const hid_type& _id)
{
  guard_type _grd (mtx_);
  auto       _itf = cast_funct_events_.find (_id);

  if (cast_funct_events_.end () == _itf)
    {
      XULOG_ERROR ("function for cast id event not found, " << _id);
      return nullptr;
    }

  auto _ret = _itf->second (_src);
  return const_cast<libs::events::IEvent*> (_ret);
}


bool
EventsImpl::event2xml (IEvent::ptr& _src, std::string& _xml)
{
  UASSERT (_src);

  try
    {
      std::stringstream            _istr;
      boost::archive::xml_oarchive _xmla (_istr, boost::archive::no_header);

      _xmla& BOOST_SERIALIZATION_NVP (_src);
      _xml = _istr.str ();
    }
  catch (std::exception& _e)
    {
      const std::string _txt = std::string ("EventsImpl::event2xml: uuu_exception, ") + _e.what () + ", " + _src->get_mid ();
      XULOG_ERROR (_txt);
      return false;
    }
  return true;
}


bool
EventsImpl::xml2event (const std::string& _xml, IEvent::ptr& _dst)
{
  std::stringstream            _istr (_xml);
  boost::archive::xml_iarchive _xmla (_istr, boost::archive::no_header);

  try
    {
      _xmla >> BOOST_SERIALIZATION_NVP (_dst);
      UASSERT (_dst);
      _dst->sync_txt2val ();
    }
  catch (std::exception& _e)
    {
      const std::string _txt = std::string ("EventsImpl::xml2event: uuu_exception, ") + _e.what ();
      XULOG_ERROR (_txt);
      return false;
    }
  return true;
}

}}}      // namespace dlls::devents::impl
