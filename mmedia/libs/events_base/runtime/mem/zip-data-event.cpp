/**
\file       zip-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "zip-data-event.hpp"

namespace libs::events_base::runtime::mem
{
ZipDataEvent::ZipDataEvent (const Acessor& pha)
{
}

auto
ZipDataEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return ZipDataEvent::gen_get_mid ();
}


ZipDataEvent::ZipDataEvent (
  ::utils::dbufs::video::IVideoBuf::raw_ptr buf,
  const number_buf_type&                    number_buf,
  id_buf_type                               id) :

  size_zip_buf_ (zip_buf_.size ()), id_zip_buf_ (std::move (id)),
  number_zip_buf_ (number_buf)
{
  utils::dbufs::video::helpers::copy_video_buf2vector (buf, zip_buf_);
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
ZipDataEvent::ZipDataEvent (
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
ZipDataEvent::ZipDataEvent (const ZipDataEvent& src) :
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
ZipDataEvent&
ZipDataEvent::operator= (const ZipDataEvent& src)
{
  ZipDataEvent temp (src);
  std::swap (*this, temp);

  id_buf_     = src.id_buf_;
  number_buf_ = src.number_buf_;
  return *this;
}
#endif

auto
ZipDataEvent::get_zip () const -> const ZipDataEvent::zip_buf_type&
{
  return zip_buf_;
}


auto
ZipDataEvent::update_zip () -> ZipDataEvent::zip_buf_type&
{
  return zip_buf_;
}


void
ZipDataEvent::update_zip (::utils::dbufs::video::IVideoBuf::raw_ptr& buf)
{
  utils::dbufs::video::helpers::copy_video_buf2vector (buf, zip_buf_);
  size_zip_buf_ = zip_buf_.size ();
}


auto
ZipDataEvent::get_size () const -> std::size_t
{
  return size_zip_buf_;
}


auto
ZipDataEvent::get_id () const -> const ZipDataEvent::id_buf_type&
{
  return id_zip_buf_;
}


void
ZipDataEvent::set_id (const id_buf_type& id)
{
  id_zip_buf_ = id;
}


auto
ZipDataEvent::get_number () const -> const ZipDataEvent::number_buf_type&
{
  return number_zip_buf_;
}


void
ZipDataEvent::set_number (const number_buf_type& number_buf)
{
  number_zip_buf_ = number_buf;
}


auto
ZipDataEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< ZipDataEvent > (this, deep);
}


void
ZipDataEvent::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< ZipDataEvent > (src);
  super::copy_int (src);

  zip_buf_        = dsrc->zip_buf_;
  size_zip_buf_   = dsrc->size_zip_buf_;
  id_zip_buf_     = dsrc->id_zip_buf_;
  number_zip_buf_ = dsrc->number_zip_buf_;
}


template< class Archive >
void
ZipDataEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (zip_buf_);
  arh& BOOST_SERIALIZATION_NVP (size_zip_buf_);
  arh& BOOST_SERIALIZATION_NVP (id_zip_buf_);
  arh& BOOST_SERIALIZATION_NVP (number_zip_buf_);

  self_correct ();
}
}   // namespace libs::events_base::runtime::mem

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::runtime::mem::ZipDataEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::runtime::mem::ZipDataEvent);
