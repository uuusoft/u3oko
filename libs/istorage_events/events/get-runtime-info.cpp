//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       get-runtime-info.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "get-runtime-info.hpp"

namespace libs { namespace istorage_events { namespace events {

GetRuntimeInfo::GetRuntimeInfo (const Acessor& _ph)
{
  property_name_ = gen_get_type_text_id ();
}


GetRuntimeInfo::~GetRuntimeInfo ()
{}


::libs::events::IEvent::ptr
GetRuntimeInfo::clone_int (const ::libs::events::TypeCloneEvent& _deep) const
{
  return helper_impl_clone_funct<GetRuntimeInfo> (this, _deep);
}


void
GetRuntimeInfo::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (GetRuntimeInfo);
  super::copy_int (_src);
  id_path_      = _dsrc->id_path_;
  stream_infos_ = _dsrc->stream_infos_;
  return;
}


template <class Archive>
void
GetRuntimeInfo::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (id_path_);
  ar& BOOST_SERIALIZATION_NVP (stream_infos_);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::GetRuntimeInfo);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::GetRuntimeInfo);
