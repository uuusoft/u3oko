/**
\file       params-video-diff-prop.cpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "params-video-diff-prop.hpp"

namespace libs::ievents::props::videos::gens::diff
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


bool
ParamsVideoDiffProp::self_test () const
{
  if (val_filling_ <= 0)
  {
    return false;
  }
  return true;
}


template< class Archive >
void
ParamsVideoDiffProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (enable_);
  arh& BOOST_SERIALIZATION_NVP (bound_filling_);
  arh& BOOST_SERIALIZATION_NVP (val_filling_);
}

void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const ParamsVideoDiffProp& src)
{
  U3_ASSERT_NT (0, "???");
}


ParamsVideoDiffProp
tag_invoke (::boost::json::value_to_tag< ParamsVideoDiffProp >, const ::boost::json::value& jvs)
{
  ParamsVideoDiffProp ret;
  U3_ASSERT_NT (0, "???");
  return ret;
}
}   // namespace libs::ievents::props::videos::gens::diff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::gens::diff::ParamsVideoDiffProp);
