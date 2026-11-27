/**
\file       info-log-session-fragment.cpp
\author     Erashov Anton erashov2026@proton.me
\date       22.02.2022
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../-libs-events-log-includes-int.hpp"
#include "info-log-session-fragment.hpp"

namespace libs::events_log::events
{
#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
InfoLogSessionFragment::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (data_);
  arh& BOOST_SERIALIZATION_NVP (off_);
  arh& BOOST_SERIALIZATION_NVP (size_);
}
#endif

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoLogSessionFragment& src)
{
  jvs = {
    { "data", src.data_ },
    { "off", src.off_ },
    { "size", src.size_ }
  };
}


auto
tag_invoke (::boost::json::value_to_tag< InfoLogSessionFragment >, const ::boost::json::value& jvs) -> InfoLogSessionFragment
{
  InfoLogSessionFragment ret;
  ret.data_ = jvs.at ("data").as_string ();
  ret.off_  = ::libs::utility::json::get_uint64 (jvs.at ("off"));
  ret.size_ = ::libs::utility::json::get_uint64 (jvs.at ("size"));
  return ret;
}
}   // namespace libs::events_log::events

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_log::events::InfoLogSessionFragment);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_log::events::InfoLogSessionFragment);
