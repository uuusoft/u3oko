//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       event-buffs-info.cpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "event-buffs-info.hpp"

namespace libs { namespace events { namespace buff {

EventBuffsInfo::EventBuffsInfo (const off_buff_type& _src, const off_buff_type& _dst) :
  indx_sbuff_ (_src),
  indx_dbuff_ (_dst)
{}


EventBuffsInfo::~EventBuffsInfo ()
{}


void
EventBuffsInfo::check (bool _check_src, bool _check_dst) const
{
  CHECK_STATE (!_check_src || utils::dbuffs::video::consts::offs::invalid != indx_sbuff_, "failed, invalid src");
  CHECK_STATE (!_check_dst || utils::dbuffs::video::consts::offs::invalid != indx_dbuff_, "failed, invalid dst");
  return;
}


void
EventBuffsInfo::load (const base_functs::xml::itn& _node)
{
  pugi::xml_attribute _sindx = _node->attribute ("sindx");
  pugi::xml_attribute _dindx = _node->attribute ("dindx");

  if (!_sindx || !_dindx)
    {
      XULOG_WARNING ("failed load EventBuffsInfo");
      return;
    }

  indx_sbuff_ = utils::dbuffs::video::consts::offs::str2eoffbuff (_sindx.as_string ());
  indx_dbuff_ = utils::dbuffs::video::consts::offs::str2eoffbuff (_dindx.as_string ());
  load_int (_node);
  return;
}


void
EventBuffsInfo::load_int (const base_functs::xml::itn& _node)
{
  return;
}


template <class Archive>
void
EventBuffsInfo::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (indx_sbuff_);
  ar& BOOST_SERIALIZATION_NVP (indx_dbuff_);
  return;
}

}}}      // namespace libs::events::buff

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::events::buff::EventBuffsInfo);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::events::buff::EventBuffsInfo);
