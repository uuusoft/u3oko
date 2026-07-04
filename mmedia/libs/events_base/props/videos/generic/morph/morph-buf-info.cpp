/**
\file       morph-buf-info.cpp
\date       08.03.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_events_base_lib
*/
#include "../../../../events-base-includes_int.hpp"
#include "morph-buf-info.hpp"

namespace libs::events_base::props::videos::generic::morph
{
MorphBuffInfo::MorphBuffInfo (
  syn::off_buf_type     sindx_diff,
  syn::off_buf_type     bindx_diff,
  morph_operations_type ops) :
  sindx_diff_ (std::move (sindx_diff)),
  bindx_diff_ (std::move (bindx_diff)),
  morph_operations_ (std::move (ops))
{
}


template< class Archive >
void
MorphBuffInfo::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& BOOST_SERIALIZATION_NVP (sindx_diff_);
  arh& BOOST_SERIALIZATION_NVP (bindx_diff_);
  arh& BOOST_SERIALIZATION_NVP (morph_operations_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jvs, const MorphBuffInfo& src)
{
  jvs = { { "sindx_diff", src.sindx_diff_ },
          { "bindx_diff", src.bindx_diff_ },
          { "morph_operations", ::boost::json::value_from (src.morph_operations_) } };
}


auto
tag_invoke (::boost::json::value_to_tag< MorphBuffInfo >, const ::boost::json::value& jvs) -> MorphBuffInfo
{
  const ::boost::json::object& obj = jvs.as_object ();
  MorphBuffInfo                ret;

  ::libs::utility::json::extract (obj, ret.sindx_diff_, "sindx_diff");
  ::libs::utility::json::extract (obj, ret.bindx_diff_, "bindx_diff");
  ret.morph_operations_ = ::boost::json::value_to< MorphBuffInfo::morph_operations_type > (jvs.at ("morph_operations"));
  return ret;
}
}   // namespace libs::events_base::props::videos::generic::morph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::videos::generic::morph::MorphBuffInfo);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::videos::generic::morph::MorphBuffInfo);
