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
BuffEvent::BuffEvent (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


BuffEvent::BuffEvent (::utils::dbufs::video::IVideoBuf::cptr& buf)
{
  if (buf)
  {
    auto impl = ::libs::helpers::check::ptr (::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ());
    buf_      = impl->create (buf->getraw_buf () ? buf->getraw_buf ()->get_data_size () : 0);
    buf_->clone (&*buf, 100.0F);
  }

  property_name_ = gen_get_mid ();
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
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BuffEvent > (src);
  super::copy_int (src);
  U3_ASSERT_SIGNAL ("unimplemented");
}

#ifdef U3_FAKE_DISABLE
template< class Archive >
void
BuffEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
template void BuffEvent::s1erialize< boost::archive::text_iarchive > (boost::archive::text_iarchive& ar, const std::uint32_t);
template void BuffEvent::s1erialize< boost::archive::text_oarchive > (boost::archive::text_oarchive& ar, const std::uint32_t);
#endif
}   // namespace libs::ievents::runtime::mem

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::ievents::runtime::mem::BuffEvent );
// U3_BOOST_SERIALIZE_ALL_ARCHIVES( ::libs::ievents::runtime::mem::BuffEvent );
