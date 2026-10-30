/**
\file       info-buf-video-diff-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../../../events-base-includes_int.hpp"
#include "info-buf-video-diff-prop.hpp"

namespace libs::events_base::props::videos::gens::diff
{
#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
InfoBuffVideoDiffProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (bindx_diff_);
  arh& BOOST_SERIALIZATION_NVP (op_);
}
#endif

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const InfoBuffVideoDiffProp& src)
{
  ::libs::utility::checks::assert_soft (0, "???");
}


auto
tag_invoke (::boost::json::value_to_tag< InfoBuffVideoDiffProp >, const ::boost::json::value& jvs) -> InfoBuffVideoDiffProp
{
  InfoBuffVideoDiffProp ret;
  ::libs::utility::checks::assert_soft (0, "???");
  return ret;
}
}   // namespace libs::events_base::props::videos::gens::diff

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp);
