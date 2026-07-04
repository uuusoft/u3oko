/**
\file       info-cpu-event.cpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_events_base_lib
*/
#include "../../events-base-includes_int.hpp"
#include "info-cpu-event.hpp"

namespace libs::events_base::props::hardware
{
InfoCPUEvent::InfoCPUEvent (
  const Acessor&      ph,
  const syn::CpuExts& simd,
  const std::uint32_t count_cpu) :
  count_cpu_ (count_cpu),
  simd_ (simd)
{
  sync_val2txt ();
}


auto
InfoCPUEvent::get_mid_int () const -> const ::libs::events::IEvent::hid_type&
{
  return InfoCPUEvent::gen_get_mid ();
}


auto
InfoCPUEvent::get_cpu_type () const -> syn::CpuExts
{
  return simd_;
}


void
InfoCPUEvent::set_cpu_type (const syn::CpuExts& type)
{
  simd_ = type;
  sync_val2txt ();
}


auto
InfoCPUEvent::get_cpu_count () const -> std::uint32_t
{
  return count_cpu_;
}


void
InfoCPUEvent::set_cpu_count (const std::uint32_t count_cpu)
{
  count_cpu_ = count_cpu;
}


auto
InfoCPUEvent::clone_int (const ::libs::events::Deeps& deep) const -> ::libs::events::IEvent::ptr
{
  return ::libs::events::deep_clone< InfoCPUEvent > (this, deep);
}


void
InfoCPUEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  text_simd_ = obj.at ("text_simd").as_string ();
  simd_      = ::libs::utility::casts::static_cast_helper< syn::CpuExts > (::libs::utility::json::get_uint32 (obj.at ("simd")));
  count_cpu_ = ::libs::utility::json::get_uint32 (obj.at ("count_cpu"));
}


void
InfoCPUEvent::save_json_int (::boost::json::object& obj) const
{
  super::save_json_int (obj);

  obj["text_simd"] = text_simd_;
  obj["simd"]      = U3_CAST_UINT32_FORCE (simd_);
  obj["count_cpu"] = count_cpu_;
}


void
InfoCPUEvent::sync_txt2val_int ()
{
  ::libs::utility::sys::cpu::TextExtCpu texter;
  simd_ = texter.get_val (text_simd_);
}


void
InfoCPUEvent::sync_val2txt_int ()
{
  ::libs::utility::sys::cpu::TextExtCpu texter;
  text_simd_ = texter.get_text (simd_);
}


void
InfoCPUEvent::copy_int (const IEvent::craw_ptr src)
{
  auto dsrc = ::libs::iproperties::helpers::dbg_check_copy_event< InfoCPUEvent > (src);
  super::copy_int (src);

  text_simd_ = dsrc->text_simd_;
  simd_      = dsrc->simd_;
  count_cpu_ = dsrc->count_cpu_;
}


template< class Archive >
void
InfoCPUEvent::serialize (Archive& arh, const std::uint32_t /* file_version */)
{
  arh& U3_BOOST_SERIALIZE_MAKE_NVP ("olibsoevents_baseoEvent", super);
  arh& BOOST_SERIALIZATION_NVP (text_simd_);
  arh& BOOST_SERIALIZATION_NVP (simd_);
  arh& BOOST_SERIALIZATION_NVP (count_cpu_);
}
}   // namespace libs::events_base::props::hardware

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events_base::props::hardware::InfoCPUEvent);
U3_BOOST_ADD_SERIALIZE_ARCH (::libs::events_base::props::hardware::InfoCPUEvent);
