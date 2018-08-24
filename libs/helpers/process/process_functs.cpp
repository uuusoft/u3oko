//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       process_functs.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "process_functs.hpp"

namespace libs { namespace helpers { namespace process {

int
get_id ()
{
  return getpid ();
}


signed long long
get_start_time ()
{
  signed long long _ret = 0;

#if defined(UUU_OS_WIN32_DESKTOP)
  {
    FILETIME     _tcreate;
    FILETIME     _texit;
    FILETIME     _tkernel;
    FILETIME     _tuser;
    const HANDLE _process = GetCurrentProcess ();

    CHECK_CALL (GetProcessTimes (_process, &_tcreate, &_texit, &_tkernel, &_tuser), "failed call GetProcessTimes");
    _ret = (UUU_ICAST_INT64 (_tcreate.dwHighDateTime) << 32) | _tcreate.dwLowDateTime;
  }
#endif
  return _ret;
}

}}}      // namespace libs::helpers::process
