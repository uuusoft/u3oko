//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       get-statistic-info.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       23.07.2018
\copyright  www.uuusoft.com
\project    uuu_istorage_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "get-statistic-info.hpp"

namespace libs { namespace istorage_events { namespace events {

GetStatisticInfo::GetStatisticInfo (const Acessor& _ph) :
  use_size_ (0)
{
  property_name_ = gen_get_mid ();
}


GetStatisticInfo::~GetStatisticInfo ()
{}


::libs::events::IEvent::ptr
GetStatisticInfo::clone_int (const ::libs::events::DeepEventCloneType& _deep) const
{
  return helper_impl_clone_funct<GetStatisticInfo> (this, _deep);
}


void
GetStatisticInfo::copy_int (const IEvent::craw_ptr _src)
{
  CHECK_STATE_COPY_EVENT (GetStatisticInfo);
  super::copy_int (_src);
  use_size_ = _dsrc->use_size_;
  return;
}


template <class Archive>
void
GetStatisticInfo::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_BASE_OBJECT_NVP (super);
  ar& BOOST_SERIALIZATION_NVP (use_size_);
  return;
}

}}}      // namespace libs::istorage_events::events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::istorage_events::events::GetStatisticInfo);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::istorage_events::events::GetStatisticInfo);
