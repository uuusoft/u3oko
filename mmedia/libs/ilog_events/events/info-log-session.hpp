#pragma once
/**
\file       info-log-session.hpp
\author     Erashov Anton erashov2026@proton.me
\date       24.05.2022
\project    uuu_ilog_events
*/

namespace libs::ilog_events::events
{
struct InfoLogSession final {
  // ext types
  using id_session_type = std::string;

  explicit InfoLogSession (
    const id_session_type& session_id        = "",
    std::uint64_t          size_session_data = 0);

  virtual ~InfoLogSession ();

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  id_session_type session_id_;          //<
  std::uint64_t   size_session_data_;   //<
};

void           tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const InfoLogSession& src);
InfoLogSession tag_invoke (::boost::json::value_to_tag< InfoLogSession >, const ::boost::json::value& jv);
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::InfoLogSession);
