/**
\file       info-log-session-fragment.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       22.02.2022
\project    u3_ilog_events
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../includes_int.hpp"
#include "info-log-session-fragment.hpp"

namespace libs::ilog_events::events
{
template< class Archive >
void
InfoLogSessionFragment::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (data_);
  arh& BOOST_SERIALIZATION_NVP (off_);
  arh& BOOST_SERIALIZATION_NVP (size_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoLogSessionFragment& src)
{
  jvs = {
    { "data", src.data_ },
    { "off", src.off_ },
    { "size", src.size_ }
  };
}


InfoLogSessionFragment
tag_invoke (::boost::json::value_to_tag< InfoLogSessionFragment >, const ::boost::json::value& jvs)
{
  InfoLogSessionFragment ret;
  ret.data_ = jvs.at ("data").as_string ();
  ret.off_  = ::libs::helpers::json::get_uint32 (jvs.at ("off"));
  ret.size_ = ::libs::helpers::json::get_uint32 (jvs.at ("size"));
  return ret;
}
}   // namespace libs::ilog_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::events::InfoLogSessionFragment);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ilog_events::events::InfoLogSessionFragment);
