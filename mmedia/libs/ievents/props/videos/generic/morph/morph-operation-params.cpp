/**
\file       morph-operation-params.cpp
\date       08.03.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../../../includes_int.hpp"
#include "morph-operation-params.hpp"

namespace libs::ievents::props::videos::generic::morph
{
MorphOperationParams::MorphOperationParams (
  const MorphOps&    type,
  const std::int32_t size_spot,
  const std::int32_t bound_filling,
  const std::int32_t val_filling) :

  size_spot_ (size_spot),
  bound_filling_ (bound_filling),
  morph_type_ (type),
  val_filling_ (val_filling)
{
}


bool
MorphOperationParams::self_test () const
{
  if (size_spot_ > 11)
  {
    U3_XLOG_ERROR ("invalid size spot" + VTOLOG (size_spot_));
    return false;
  }
  return true;
}


MorphOperationParams::~MorphOperationParams ()
{
}


template< class Archive >
void
MorphOperationParams::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (morph_type_);
  ar& BOOST_SERIALIZATION_NVP (size_spot_);
  ar& BOOST_SERIALIZATION_NVP (bound_filling_);
  ar& BOOST_SERIALIZATION_NVP (val_filling_);
}


void
tag_invoke (::boost::json::value_from_tag, ::boost::json::value& jv, const MorphOperationParams& src)
{
  jv = {
    { "morph_type", U3_CAST_UINT32_FORCE (src.morph_type_) },
    { "size_spot", src.size_spot_ },
    { "bound_filling", src.bound_filling_ },
    { "val_filling", src.val_filling_ }
  };
}


MorphOperationParams
tag_invoke (::boost::json::value_to_tag< MorphOperationParams >, const ::boost::json::value& jv)
{
  MorphOperationParams ret;

  ret.morph_type_    = ::boost::json::value_to< MorphOps > (jv.at ("morph_type"));
  ret.size_spot_     = ::libs::helpers::json::get_uint32 (jv.at ("size_spot"));
  ret.bound_filling_ = ::libs::helpers::json::get_uint32 (jv.at ("bound_filling"));
  ret.val_filling_   = ::libs::helpers::json::get_uint32 (jv.at ("val_filling"));
  return ret;
}
}   // namespace libs::ievents::props::videos::generic::morph

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::videos::generic::morph::MorphOperationParams);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::videos::generic::morph::MorphOperationParams);
