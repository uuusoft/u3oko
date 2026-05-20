#pragma once
/**
\file       info-log-session-fragment.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    uuu_ilog_events
*/

namespace libs::ilog_events::events
{
struct InfoLogSessionFragment final {
  // ext types
  using data_session_type = std::string;

  InfoLogSessionFragment ();
  virtual ~InfoLogSessionFragment ();

  template< class Archive >
  void serialize (Archive& ar, const std::uint32_t /* file_version */);

  data_session_type data_;   //<
  unsigned long     off_;    //<
  unsigned long     size_;   //<
};

void                   tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const InfoLogSessionFragment& src);
InfoLogSessionFragment tag_invoke (::boost::json::value_to_tag< InfoLogSessionFragment >, const ::boost::json::value& jv);
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::InfoLogSessionFragment);
