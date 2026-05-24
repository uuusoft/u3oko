/**
\file       event-bufs-info.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "event-bufs-info.hpp"

namespace libs::events::buf
{
EventBufsInfo::EventBufsInfo (
  const syn::off_buf_type& src,
  const syn::off_buf_type& dst) :
  indx_sbuf_ (src),
  indx_dbuf_ (dst)
{
}


EventBufsInfo::~EventBufsInfo ()
{
}


void
EventBufsInfo::check (bool check_src, bool check_dst)
{
  U3_CHECK (!check_src || utils::dbufs::video::consts::offs::invalid != indx_sbuf_, "invalid src");
  U3_CHECK (!check_dst || utils::dbufs::video::consts::offs::invalid != indx_dbuf_, "invalid dst");
  check_int ();
  correct_int ();
}


void
EventBufsInfo::check_int ()
{
}


void
EventBufsInfo::correct_int ()
{
}


template< class Archive >
void
EventBufsInfo::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (indx_sbuf_);
  ar& BOOST_SERIALIZATION_NVP (indx_dbuf_);
}

#if 0
bool
is_valid_node (const ::pugi::xml_named_node_iterator& node)
{
  return node->name () == consts::node_name ? true : false;
}
#endif

void
tag_invoke (
  ::boost::json::value_from_tag,
  ::boost::json::value& jv,
  const EventBufsInfo&  src)
{
  jv = {
    { "indx_sbuf", src.indx_sbuf_ },
    { "indx_dbuf", src.indx_dbuf_ }
  };
}


EventBufsInfo
tag_invoke (
  ::boost::json::value_to_tag< EventBufsInfo >,
  const ::boost::json::value& jv)
{
  EventBufsInfo                ret;
  const ::boost::json::object& obj = jv.as_object ();

  ret.indx_sbuf_ = obj.at ("indx_sbuf").as_string ();
  ret.indx_dbuf_ = obj.at ("indx_dbuf").as_string ();
  return ret;
}
}   // namespace libs::events::buf

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::buf::EventBufsInfo);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::events::buf::EventBufsInfo);
