/**
\file       info-cpu-event.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_ievents_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../../includes_int.hpp"
#include "info-cpu-event.hpp"

namespace libs::ievents::props::hardware
{
InfoCPUEvent::InfoCPUEvent (
  const Acessor&                            ph,
  const ::libs::helpers::sys::cpu::CpuExts& simd,
  const std::uint32_t                       count_cpu) :

  count_cpu_ (count_cpu),
  simd_ (simd)
{
  property_name_ = gen_get_mid ();
  sync_val2txt ();
}


InfoCPUEvent::~InfoCPUEvent ()
{
}


::libs::helpers::sys::cpu::CpuExts
InfoCPUEvent::get_cpu_type () const
{
  return simd_;
}


void
InfoCPUEvent::set_cpu_type (const ::libs::helpers::sys::cpu::CpuExts& type)
{
  simd_ = type;
  sync_val2txt ();
}


std::uint32_t
InfoCPUEvent::get_cpu_count () const
{
  return count_cpu_;
}


void
InfoCPUEvent::set_cpu_count (const std::uint32_t count_cpu)
{
  count_cpu_ = count_cpu;
}


::libs::events::IEvent::ptr
InfoCPUEvent::clone_int (const ::libs::events::Deeps& deep) const
{
  return ::libs::events::deep_clone< InfoCPUEvent > (this, deep);
}


void
InfoCPUEvent::load_json_int (const ::boost::json::object& obj)
{
  super::load_json_int (obj);

  text_simd_ = obj.at ("text_simd").as_string ();
  simd_      = U3_CAST_STATIC< ::libs::helpers::sys::cpu::CpuExts > (::libs::helpers::json::get_uint32 (obj.at ("simd")));
  count_cpu_ = ::libs::helpers::json::get_uint32 (obj.at ("count_cpu"));
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
  ::libs::helpers::sys::cpu::TextExtCpu texter;
  simd_ = texter.get_val (text_simd_);
}


void
InfoCPUEvent::sync_val2txt_int ()
{
  ::libs::helpers::sys::cpu::TextExtCpu texter;
  text_simd_ = texter.get_text (simd_);
}


void
InfoCPUEvent::copy_int (const IEvent::craw_ptr src)
{
  U3_CHECK_COPY_EVENT (InfoCPUEvent);
  super::copy_int (src);

  text_simd_ = dsrc->text_simd_;
  simd_      = dsrc->simd_;
  count_cpu_ = dsrc->count_cpu_;
}


template< class Archive >
void
InfoCPUEvent::serialize (Archive& ar, const std::uint32_t /* file_version */)
{
  ar& U3_BOOST_SERIALIZATION_BASE_OBJECT_NVP ("olibsoieventsoEvent", super);
  ar& BOOST_SERIALIZATION_NVP (text_simd_);
  ar& BOOST_SERIALIZATION_NVP (simd_);
  ar& BOOST_SERIALIZATION_NVP (count_cpu_);
}
}   // namespace libs::ievents::props::hardware

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::hardware::InfoCPUEvent);
U3_BOOST_SERIALIZE_ALL_ARCHIVES (::libs::ievents::props::hardware::InfoCPUEvent);
