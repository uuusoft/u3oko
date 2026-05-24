/**
\file       buf-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "buf-event.hpp"

namespace libs::ievents::runtime::mem
{
BuffEvent::BuffEvent (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


BuffEvent::BuffEvent (::utils::dbufs::video::IVideoBuf::cptr& buf)
{
  if (buf)
  {
    auto impl = ::libs::helpers::check::ptr (::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ());
    buf_      = impl->create (buf->getraw_buf () ? buf->getraw_buf ()->get_data_size () : 0);
    buf_->clone (&*buf, 100.0f);
  }

  property_name_ = gen_get_mid ();
}


BuffEvent::~BuffEvent ()
{
}


::utils::dbufs::video::IVideoBuf::ptr&
BuffEvent::get_buf ()
{
  return buf_;
}


::libs::events::IEvent::ptr
BuffEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< BuffEvent > (this, deep);
}


void
BuffEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (BuffEvent);
  super::copy_int (src);
  // buf_
  U3_ASSERT_SIGNAL ("unimplemented");
}

#if 0
template< class Archive >
void
BuffEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
template void BuffEvent::s1erialize< boost::archive::text_iarchive > (boost::archive::text_iarchive& ar, const std::uint32_t);
template void BuffEvent::s1erialize< boost::archive::text_oarchive > (boost::archive::text_oarchive& ar, const std::uint32_t);
#endif
}   // namespace libs::ievents::runtime::mem

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::mem::BuffEvent );
// U3_BOOST_SERIALIZE_ALL_ARCHIVES( ::libs::ievents::runtime::mem::BuffEvent );
