/**
\file       params-video-diff-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/
#include "../../../../events-base-includes_int.hpp"
#include "params-video-diff-prop.hpp"

namespace libs::events_base::props::videos::gens::diff
{
ParamsVideoDiffProp::ParamsVideoDiffProp (
  bool         enable,
  std::int16_t bound_filling,
  std::int16_t val_filling) :
  enable_ (enable),
  bound_filling_ (bound_filling),
  val_filling_ (val_filling)
{
}


auto
ParamsVideoDiffProp::self_test () const -> bool
{
  if (val_filling_ <= 0)
  {
    return false;
  }
  return true;
}

#if (U3_USE_BOOST_SERIALIZTION)
template< class Archive >
void
ParamsVideoDiffProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (enable_);
  arh& BOOST_SERIALIZATION_NVP (bound_filling_);
  arh& BOOST_SERIALIZATION_NVP (val_filling_);
}
#endif

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const ParamsVideoDiffProp& src)
{
  ::libs::utility::checks::assert_soft (0, "???");
}


auto
tag_invoke (::boost::json::value_to_tag< ParamsVideoDiffProp >, const ::boost::json::value& jvs) -> ParamsVideoDiffProp
{
  ParamsVideoDiffProp ret;
  ::libs::utility::checks::assert_soft (0, "???");
  return ret;
}
}   // namespace libs::events_base::props::videos::gens::diff

U3_BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::gens::diff::ParamsVideoDiffProp);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::gens::diff::ParamsVideoDiffProp);
