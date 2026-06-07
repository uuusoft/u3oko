/**
\file       info-log-session.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.05.2022
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "info-log-session.hpp"

namespace libs::ilog_events::events
{
InfoLogSession::InfoLogSession (const id_session_type& session_id, std::uint64_t size_session_data) :
  session_id_ (session_id),
  size_session_data_ (size_session_data)
{
}


template< class Archive >
void
InfoLogSession::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (session_id_);
  arh& BOOST_SERIALIZATION_NVP (size_session_data_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoLogSession& src)
{
  jvs = {
    { "session_id", src.session_id_ },
    { "size_session_data", src.size_session_data_ }
  };
}


InfoLogSession
tag_invoke (::boost::json::value_to_tag< InfoLogSession >, const ::boost::json::value& jvs)
{
  InfoLogSession ret;
  ret.session_id_        = jvs.at ("session_id").as_string ();
  ret.size_session_data_ = ::libs::helpers::json::get_uint64 (jvs.at ("size_session_data"));
  return ret;
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::InfoLogSession);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::InfoLogSession);
