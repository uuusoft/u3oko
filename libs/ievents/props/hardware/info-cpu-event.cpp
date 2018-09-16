//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       info-cpu-event.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../../includes_int.hpp"
#include "info-cpu-event.hpp"

namespace libs { namespace ievents { namespace props { namespace hardware {

InfoCPUEvent::InfoCPUEvent (const Acessor& _ph, const TypeExtCpu& _simd, const unsigned short _count_cpu) :
  count_cpu_ (_count_cpu),
  simd_ (_simd)
{
  property_name_ = gen_get_mid ();
  sync_val2txt ();
}


InfoCPUEvent::~InfoCPUEvent ()
{}


TypeExtCpu
InfoCPUEvent::get_type () const
{
  return simd_;
}


void
InfoCPUEvent::set_type (const TypeExtCpu& _type)
{
  simd_ = _type;
  sync_val2txt ();
  return;
}


unsigned short
InfoCPUEvent::get_count () const
{
  return count_cpu_;
}


void
InfoCPUEvent::set_count (const unsigned short _count_cpu)
{
  count_cpu_ = _count_cpu;
  return;
}


::libs::events::IEvent::ptr
InfoCPUEvent::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<InfoCPUEvent> (this, _deep);
}


void
InfoCPUEvent::load_int (const base_functs::xml::itn& _node)
{
  super::load_int (_node);

  base_functs::xml::ritn _params = _node->children ("param");
  base_functs::xml::itn  _param  = _params.begin ();

  while (_param != _params.end ())
    {
      ::libs::icore::xml::helpers::load (
        _param,
        "simd",
        [this](const std::string& _txt) {
          text_simd_ = _txt;

          sync_txt2val ();
          sync_val2txt ();
          return;
        });

      ::libs::icore::xml::helpers::load<unsigned short> (_param, "count", count_cpu_);

      ++_param;
    }

  //sync_txt2val();
  self_correct ();
  return;
}


void
InfoCPUEvent::sync_txt2val_int ()
{
  TextExtCpu _texter;
  simd_ = _texter.get_val (text_simd_);
  return;
}


void
InfoCPUEvent::sync_val2txt_int ()
{
  TextExtCpu _texter;
  text_simd_ = _texter.get_text (simd_);
  return;
}


void
InfoCPUEvent::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (InfoCPUEvent);
  super::copy_int (_src);
  text_simd_ = _dsrc->text_simd_;
  simd_      = _dsrc->simd_;
  count_cpu_ = _dsrc->count_cpu_;
  return;
}


template <class Archive>
void
InfoCPUEvent::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (text_simd_);
  ar& BOOST_SERIALIZATION_NVP (simd_);
  ar& BOOST_SERIALIZATION_NVP (count_cpu_);
  return;
}

}}}}      // namespace libs::ievents::props::hardware

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ievents::props::hardware::InfoCPUEvent);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ievents::props::hardware::InfoCPUEvent);
