/**
\file       info-log-session.cpp
\author     Erashov Anton erashov2026@proton.me
\date       24.05.2022
\project    u3_events_log
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "info-log-session.hpp"

namespace libs::events_log::events
{
InfoLogSession::InfoLogSession (id_session_type session_id, std::uint64_t size_session_data) :
  session_id_ (std::move (session_id)),
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


auto
tag_invoke (::boost::json::value_to_tag< InfoLogSession >, const ::boost::json::value& jvs) -> InfoLogSession
{
  InfoLogSession ret;
  ret.session_id_        = jvs.at ("session_id").as_string ();
  ret.size_session_data_ = ::libs::utility::json::get_uint64 (jvs.at ("size_session_data"));
  return ret;
}
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::InfoLogSession);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::InfoLogSession);
