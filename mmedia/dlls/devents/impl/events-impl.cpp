/**
\file       events-impl.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       21.07.2017
\project    u3_devents_dlls
*/
// #define U3_USE_DEB_LOG_LEVEL
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../generics-devents-includes_int.hpp"
#include "events-impl.hpp"

namespace dlls::devents::impl
{
EventsImpl::EventsImpl ()
{
  {
    lock_type lock (mtx_);
    construct_func_event ();
  }
}


EventsImpl::~EventsImpl ()
{
}


syn::IEvent::ptr
EventsImpl::get (const hid_type& id, const char* debid)
{
  lock_type lock (mtx_);
  auto      itf = gen_func_events_.find (id);

  if (gen_func_events_.end () == itf)
  {
    U3_XLOG_ERROR ("function for create id event not found" + TOLOG (id));
    return syn::IEvent::ptr ();
  }

  auto ret = itf->second ();
  U3_ASSERT (ret);
  ++counter_create_events_[id];

#if 0
  if (counter_create_events_[id] >= 1024 && 0 == counter_create_events_[id] % 1024)
  {
    U3_XLOG_MARK ("dllevents" + TOLOG (id) + VTOLOG (counter_create_events_[id]) + (debid ? TOLOG (std::string (debid)) : ""));
  }
#endif
  return ret;
}


syn::IEvent::ptr
EventsImpl::clone (const syn::IEvent::craw_ptr src, const ::libs::events::Deeps& type)
{
  ++counter_clone_events_[src->gen_get_mid ()];
  return src->clone (type);
}


void*
EventsImpl::dcast (syn::IEvent::craw_ptr src, const hid_type& id)
{
  lock_type lock (mtx_);
  auto      itf = cast_func_events_.find (id);

  if (cast_func_events_.end () == itf)
  {
    U3_LOG_DATA_ERROR ("function for cast id event not found" + TOLOG (id));
    return nullptr;
  }

  auto ret = itf->second (src);
  return const_cast< libs::events::IEvent* > (ret);
}


bool
EventsImpl::event2xml (syn::IEvent::ptr& src, std::string& xml)
{
  U3_ASSERT (src);

  try
  {
    std::stringstream            istr;
    boost::archive::xml_oarchive xmla (istr, boost::archive::no_header);

    xmla& BOOST_SERIALIZATION_NVP (src);
    xml = istr.str ();
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what () + TOLOG (src->get_mid ()));
    return false;
  }
  return true;
}


bool
EventsImpl::xml2event (const std::string& xml, syn::IEvent::ptr& dst)
{
  std::stringstream            istr (xml);
  boost::archive::xml_iarchive xmla (istr, boost::archive::no_header);

  try
  {
    xmla >> BOOST_SERIALIZATION_NVP (dst);
    U3_ASSERT (dst);
    dst->sync_txt2val ();
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
    return false;
  }
  return true;
}


bool
EventsImpl::event2bin (syn::IEvent::ptr& src, std::ostream& bin)
{
  U3_ASSERT (src);

  try
  {
    boost::archive::binary_oarchive arc (bin);
    arc & src;
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what () + TOLOG (src->get_mid ()));
    return false;
  }
  return true;
}


bool
EventsImpl::bin2event (std::istream& bin, syn::IEvent::ptr& dst)
{
  boost::archive::binary_iarchive arc (bin);

  try
  {
    arc >> dst;
    U3_ASSERT (dst);
    dst->sync_txt2val ();
  }
  catch (std::exception& e)
  {
    U3_LOG_DATA_EXCEPT (e.what ());
    return false;
  }
  return true;
}
}   // namespace dlls::devents::impl
