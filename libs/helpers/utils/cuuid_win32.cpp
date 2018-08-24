//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       cuuid_win32.cpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "../includes_int.hpp"
#include "cuuid.hpp"
#include "mmedia/libs/events/serialize_type_to_archive_define.hpp"

namespace libs { namespace helpers { namespace utils {
#if defined(UUU_OS_WIN32_DESKTOP)

cuuid::cuuid (const GUID& _guid)
{
  std::copy (
    UUU_MEM_CAST<const unsigned char*> (&_guid),
    UUU_MEM_CAST<const unsigned char*> (&_guid) + sizeof (GUID),
    id_.begin ());
}

const GUID*
cuuid::get_guid () const
{
  return UUU_MEM_CAST<const GUID*> (id_.data);
}

#endif
}}}      // namespace libs::helpers::utils
