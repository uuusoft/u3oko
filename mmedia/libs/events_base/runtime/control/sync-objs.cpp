/**
\file       sync-objs.cpp
\date       17.03.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "sync-objs.hpp"

namespace libs::events_base::runtime::control
{
SyncObjs::SyncObjs (const Acessor& pha)
{
}


auto
SyncObjs::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return SyncObjs::gen_get_mid ();
}


#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
SyncObjs::SyncObjs (
  zip_buf_type&&         buf,
  std::size_t            size,
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
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
SyncObjs::SyncObjs (
  ::utils::dbufs::video::IVideoBuf::raw_ptr buf,
  const number_buf_type&                    number_buf,
  const id_buf_type&                        id) :

  id_zip_buf_ (id),
  number_zip_buf_ (number_buf)
{
  property_name_ = gen_get_mid ();
  utils::dbufs::video::helpers::copy_video_buf2vector (buf, zip_buf_);
  size_zip_buf_ = zip_buf_.size ();
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
SyncObjs::SyncObjs (const SyncObjs& src) :
  size_ (0)
{
  property_name_ = gen_get_mid ();
  super::operator= (src);

  if (src.get_size ())
  {
    size_ = src.get_size ();
    buf_.resize (size_);
    ::libs::utility::mem::u3copy (&src.get_zip ()[0], &buf_[0], size_);
  }
}
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
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

auto
SyncObjs::get_groups () const -> const SyncObjs::groups_type&
{
  return obj_groups_;
}


auto
SyncObjs::update_groups () -> SyncObjs::groups_type&
{
  return obj_groups_;
}


auto
SyncObjs::get_client_id () const -> const std::string&
{
  return client_id_;
}


auto
SyncObjs::update_client_id () -> std::string&
{
  return client_id_;
}

void
SyncObjs::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  action_ ? ? ? = ::boost::json::value_to< LogProcessActions > (obj.at ("action???"));
  info_         = ::boost::json::value_to< InfoLogSessionFragment > (obj.at ("info"));
  session_      = obj.at ("session").as_string ();
#endif
}


void
SyncObjs::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  obj["action???"]  = ::boost::json::value_from (action_???);
  obj["info"]       = ::boost::json::value_from (info_);
  obj["session"]    = session_;
#endif
}


auto
SyncObjs::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< SyncObjs > (this, deep);
}


void
SyncObjs::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< SyncObjs > (src);
  super::copy_int (src);

  client_id_  = dsrc->client_id_;
  obj_groups_ = dsrc->obj_groups_;
}


template< class Archive >
void
SyncObjs::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (client_id_);
  arh& BOOST_SERIALIZATION_NVP (obj_groups_);

  self_correct ();
}
}   // namespace libs::events_base::runtime::control

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::control::SyncObjs);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::control::SyncObjs);
