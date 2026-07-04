/**
\file       info-buf-video-diff-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "info-buf-video-diff-prop.hpp"

namespace libs::events_base::props::videos::gens::diff
{
template< class Archive >
void
InfoBuffVideoDiffProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (bindx_diff_);
  arh& BOOST_SERIALIZATION_NVP (op_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoBuffVideoDiffProp& src)
{
  U3_ASSERT_NT (0, "???");
}


auto
tag_invoke (::boost::json::value_to_tag< InfoBuffVideoDiffProp >, const ::boost::json::value& jvs) -> InfoBuffVideoDiffProp
{
  InfoBuffVideoDiffProp ret;
  U3_ASSERT_NT (0, "???");
  return ret;
}
}   // namespace libs::events_base::props::videos::gens::diff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp);
