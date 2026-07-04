/**
\file       event-bufs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/
#include "../includes_int.hpp"
#include "event-bufs.hpp"

namespace libs::events::buf
{
EventBufs::EventBufs (
  syn::off_buf_type src,
  syn::off_buf_type dst) :
  indx_sbuf_ (std::move (src)),
  indx_dbuf_ (std::move (dst))
{
}


void
EventBufs::check (bool check_src, bool check_dst)
{
  U3_CHECK (!check_src || utils::dbufs::video::consts::offs::invalid != indx_sbuf_, "invalid src");
  U3_CHECK (!check_dst || utils::dbufs::video::consts::offs::invalid != indx_dbuf_, "invalid dst");
  check_int ();
  correct_int ();
}


void
EventBufs::check_int ()
{
}


void
EventBufs::correct_int ()
{
}


template< class Archive >
void
EventBufs::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (indx_sbuf_);
  arh& BOOST_SERIALIZATION_NVP (indx_dbuf_);
}


void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jvs,
  const EventBufs&      src)
{
  jvs = {
    { "indx_sbuf", src.indx_sbuf_ },
    { "indx_dbuf", src.indx_dbuf_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< EventBufs >, const ::boost::json::value& jvs) -> EventBufs
{
  EventBufs                    ret;
  const ::boost::json::object& obj = jvs.as_object ();

  ret.indx_sbuf_ = obj.at ("indx_sbuf").as_string ();
  ret.indx_dbuf_ = obj.at ("indx_dbuf").as_string ();
  return ret;
}
}   // namespace libs::events::buf

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::buf::EventBufs);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events::buf::EventBufs);
