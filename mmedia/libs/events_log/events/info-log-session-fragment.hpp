#pragma once
/**
\file       info-log-session-fragment.hpp
\author     Erashov Anton erashov2026@proton.me
\date       09.09.2018
\project    u3_events_log
*/

namespace libs::events_log::events
{
struct InfoLogSessionFragment final {
  // ext types
  using data_session_type = std::string;

  InfoLogSessionFragment ()          = default;
  virtual ~InfoLogSessionFragment () = default;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  data_session_type data_ = {};   //<
  std::uint64_t     off_  = 0;    //<
  std::uint64_t     size_ = 0;    //<
};

void                   tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoLogSessionFragment& src);
InfoLogSessionFragment tag_invoke (::boost::json::value_to_tag< InfoLogSessionFragment >, const ::boost::json::value& jvs);
}   // namespace libs::events_log::events

BOOST_CLASS_EXPORT_KEY (::libs::events_log::events::InfoLogSessionFragment);
