//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       appll-part-log-info.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilog_events
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "includes_int.hpp"
#include "appll-part-log-info.hpp"

namespace libs { namespace ilog_events {

AppllPartLogInfo::AppllPartLogInfo (
  const std::string& _subsys,
  const std::string& _funct,
  const int          _line) :

  subsys_ (_subsys),
  funct_ (_funct),
  line_ (_line)
{}


AppllPartLogInfo::~AppllPartLogInfo ()
{}


template <class Archive>
void
AppllPartLogInfo::serialize (Archive& ar, const unsigned int /* file_version */)
{
  ar& BOOST_SERIALIZATION_NVP (subsys_);
  ar& BOOST_SERIALIZATION_NVP (funct_);
  ar& BOOST_SERIALIZATION_NVP (line_);
  return;
}

}}      // namespace libs::ilog_events

BOOST_CLASS_EXPORT_IMPLEMENT (::libs::ilog_events::AppllPartLogInfo);
SERIALIZE_TYPE_TO_ARCHIVES (::libs::ilog_events::AppllPartLogInfo);
