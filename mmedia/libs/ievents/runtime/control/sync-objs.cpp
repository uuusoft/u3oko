/**
\file       sync-objs.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "sync-objs.hpp"

namespace libs::ievents::runtime::control
{
SyncObjs::SyncObjs (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
  //????
}

#if 0
SyncObjs::SyncObjs (
  zip_buf_type&&         buf,
  std::size_t             size,
  const number_buf_type& number_buf,
  const id_buf_type&     id) :

  zip_buf_ (std::move (buf)),
  size_zip_buf_ (size),
  id_zip_buf_ (id),
  number_zip_buf_ (number_buf)
{
  property_name_ = gen_get_mid ();
}
#endif
#if 0
SyncObjs::SyncObjs (
  ::utils::dbufs::video::IVideoBuf::raw_ptr buf,
  const number_buf_type&                     number_buf,
  const id_buf_type&                         id) :

  id_zip_buf_ (id),
  number_zip_buf_ (number_buf)
{
  property_name_ = gen_get_mid ();
  utils::dbufs::video::helpers::copy_video_buf2vector (buf, zip_buf_);
  size_zip_buf_ = zip_buf_.size ();
}
#endif
#if 0
SyncObjs::SyncObjs (const SyncObjs& src) :
  size_ (0)
{
  property_name_ = gen_get_mid ();
  super::operator= (src);

  if (src.get_size ())
    {
      size_ = src.get_size ();
      buf_.resize (size_);
      ::libs::helpers::mem::u3copy (&src.get_zip ()[0], &buf_[0], size_);
    }
}
#endif
#if 0
SyncObjs&
SyncObjs::operator= (const SyncObjs& src)
{
  SyncObjs temp (src);
  std::swap (*this, temp);

  id_buf_     = src.id_buf_;
  number_buf_ = src.number_buf_;
  return *this;
}
#endif

SyncObjs::~SyncObjs ()
{
}


const SyncObjs::groups_type&
SyncObjs::get_groups () const
{
  return obj_groups_;
}


SyncObjs::groups_type&
SyncObjs::update_groups ()
{
  return obj_groups_;
}


const std::string&
SyncObjs::get_client_id () const
{
  return client_id_;
}


std::string&
SyncObjs::update_client_id ()
{
  return client_id_;
}

void
SyncObjs::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
#if 0  
  action_  = ::boost::json::value_to< LogProcessActions > (obj.at ("action"));
  info_    = ::boost::json::value_to< InfoLogSessionFragment > (obj.at ("info"));
  session_ = obj.at ("session").as_string ();
#endif
}


void
SyncObjs::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
#if 0  
  obj["action"]  = ::boost::json::value_from (action_);
  obj["info"]    = ::boost::json::value_from (info_);
  obj["session"] = session_;
#endif
}


::libs::events::IEvent::ptr
SyncObjs::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< SyncObjs > (this, deep);
}


void
SyncObjs::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (SyncObjs);
  super::copy_int (src);

  client_id_  = dsrc->client_id_;
  obj_groups_ = dsrc->obj_groups_;
}


template< class Archive >
void
SyncObjs::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  ar& BOOST_SERIALIZATION_NVP (client_id_);
  ar& BOOST_SERIALIZATION_NVP (obj_groups_);

  self_correct ();
}
}   // namespace libs::ievents::runtime::control

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::control::SyncObjs);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::control::SyncObjs);
