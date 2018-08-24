//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       acopy.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Реализация функции копирования блока памяти для всей системы.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"

#include "acopy.hpp"

namespace libs { namespace helpers { namespace mem {

void
acopy (const void* _src, void* _dst, std::size_t _size)
{
#if defined(UUU_CHECK_COPY_MEM) && defined(UUU_OS_WIN32_DESKTOP)
  CHECK_CALL (0 == IsBadReadPtr (_src, _size), "failed read check mem");
  CHECK_CALL (0 == IsBadWritePtr (_dst, _size), "failed write check mem");
#endif
  memcpy (_dst, _src, _size);
  return;
}

}}}      // namespace libs::helpers::mem
