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
MixMulProp::MixMulProp (const Acessor& ph)
{
  property_name_ = gen_get_mid ();
}


MixMulProp::~MixMulProp ()
{
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
  U3_CHECK_COPY_EVENT (MixMulProp);
  super::copy_int (src);
  outs_ = dsrc->outs_;
}


template< class Archive >
void
MixMulProp::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (outs_);

  self_correct ();
}
}   // namespace libs::ievents::props::mix_mul

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::mix_mul::MixMulProp);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::mix_mul::MixMulProp);
