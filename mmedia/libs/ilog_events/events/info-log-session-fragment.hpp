#pragma once
/**
\file       info-log-session-fragment.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       09.09.2018
\project    u3_ilog_events
*/

namespace libs::ilog_events::events
{
struct InfoLogSessionFragment final {
  // ext types
  using data_session_type = std::string;

  InfoLogSessionFragment ()          = default;
  virtual ~InfoLogSessionFragment () = default;

  template< class Archive >
  void serialize (Archive& arh, const std::uint32_t /* file_version */);

  data_session_type data_ = {};   //<
  unsigned long     off_  = 0;    //<
  unsigned long     size_ = 0;    //<
};

void                   tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoLogSessionFragment& src);
InfoLogSessionFragment tag_invoke (::boost::json::value_to_tag< InfoLogSessionFragment >, const ::boost::json::value& jvs);
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_KEY (::libs::ilog_events::events::InfoLogSessionFragment);
