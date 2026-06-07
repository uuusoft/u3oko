/**
\file       mix-mul-prop.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017

\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "mix-mul-prop.hpp"

namespace libs::ievents::props::mix_mul
{
MixMulProp::MixMulProp (const Acessor& pha)
{
  property_name_ = gen_get_mid ();
}


::libs::events::IEvent::ptr
MixMulProp::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< MixMulProp > (this, deep);
}


void
MixMulProp::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);
  outs_ = ::boost::json::value_to< MixMulProp::out_channels_type > (obj.at ("outs"));
}


void
MixMulProp::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);
  obj["outs"] = ::boost::json::value_from (outs_);
}


void
MixMulProp::copy_int (const IEvent::craw_ptr src)
{
  const auto* dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< MixMulProp > (src);
  super::copy_int (src);
  outs_ = dsrc->outs_;
}


template< class Archive >
void
MixMulProp::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (outs_);

  self_correct ();
}
}   // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::mix_mul::MixMulProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::mix_mul::MixMulProp);
