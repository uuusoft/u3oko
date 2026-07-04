/**
\file       buf-event.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "buf-event.hpp"

namespace libs::events_base::runtime::mem
{
BuffEvent::BuffEvent (const Acessor& pha)
{
}


BuffEvent::BuffEvent (::utils::dbufs::video::IVideoBuf::cptr& buf)
{
  if (buf)
  {
    auto impl = ::libs::utility::check::ptr (::libs::iproperties::helpers::cast_prop_demons ()->get_bufs_lockfree ()->impl ());
    buf_      = impl->create (buf->getraw_buf () ? buf->getraw_buf ()->get_size () : 0);
    buf_->clone (&*buf, 100.0F);
  }
}


auto
BuffEvent::get_buf () -> ::utils::dbufs::video::IVideoBuf::ptr&
{
  return buf_;
}


auto
BuffEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return BuffEvent::gen_get_mid ();
}


auto
BuffEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< BuffEvent > (this, deep);
}


void
BuffEvent::copy_int (const ::libs::events::IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< BuffEvent > (src);
  super::copy_int (src);
  U3_ASSERT_SIGNAL ("unimplemented");
}

#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
template< class Archive >
void
BuffEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP (super);
  arh& BOOST_SERIALIZATION_NVP (buf_);

  self_correct ();
}
template void BuffEvent::s1erialize< boost::archive::text_iarchive > (boost::archive::text_iarchive& ar, const std::uint32_t);
template void BuffEvent::s1erialize< boost::archive::text_oarchive > (boost::archive::text_oarchive& ar, const std::uint32_t);
#endif
}   // namespace libs::events_base::runtime::mem

// BOOST_CLASS_EXPORT_IMPLEMENT( ::libs::events_base::runtime::mem::BuffEvent );
// U3_BOOST_ADD_SERIALIZE_ARCH( ::libs::events_base::runtime::mem::BuffEvent );
