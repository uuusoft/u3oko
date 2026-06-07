/**
\file       zip-data-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "zip-data-event.hpp"

namespace libs::ievents::runtime::mem
{
ZipDataEvent::ZipDataEvent (const Acessor& pha) :
  size_zip_buf_ (0)
{
  property_name_ = gen_get_mid ();
}

#ifdef U3_FAKE_DISABLE
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

ZipDataEvent::ZipDataEvent (
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

#ifdef U3_FAKE_DISABLE
ZipDataEvent::ZipDataEvent (const ZipDataEvent& src) :
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
#ifdef U3_FAKE_DISABLE
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

const ZipDataEvent::zip_buf_type&
ZipDataEvent::get_zip () const
{
  return zip_buf_;
}


ZipDataEvent::zip_buf_type&
ZipDataEvent::update_zip ()
{
  return zip_buf_;
}


void
ZipDataEvent::update_zip (::utils::dbufs::video::IVideoBuf::raw_ptr& buf)
{
  utils::dbufs::video::helpers::copy_video_buf2vector (buf, zip_buf_);
  size_zip_buf_ = zip_buf_.size ();
}


std::size_t
ZipDataEvent::get_size () const
{
  return size_zip_buf_;
}


const ZipDataEvent::id_buf_type&
ZipDataEvent::get_id () const
{
  return id_zip_buf_;
}


void
ZipDataEvent::set_id (const id_buf_type& id)
{
  id_zip_buf_ = id;
}


const ZipDataEvent::number_buf_type&
ZipDataEvent::get_number () const
{
  return number_zip_buf_;
}


void
ZipDataEvent::set_number (const number_buf_type& number_buf)
{
  number_zip_buf_ = number_buf;
}


::libs::events::IEvent::ptr
ZipDataEvent::clone_int (const ::libs::events::Deeps& deep) const
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
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoruntimeoRuntimeEvent", super);
  arh& BOOST_SERIALIZATION_NVP (zip_buf_);
  arh& BOOST_SERIALIZATION_NVP (size_zip_buf_);
  arh& BOOST_SERIALIZATION_NVP (id_zip_buf_);
  arh& BOOST_SERIALIZATION_NVP (number_zip_buf_);

  self_correct ();
}
}   // namespace libs::ievents::runtime::mem

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::runtime::mem::ZipDataEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::runtime::mem::ZipDataEvent);
