//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       check_buff.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "check_buff.hpp"

namespace libs { namespace helpers { namespace mem {

bool
check_buff (void* _sbuff, const unsigned int _size)
{
  unsigned char*         _buff    = UUU_MEM_CAST<unsigned char*> (_sbuff);
  volatile bool          _read_op = false;
  std::size_t            _cindx   = 0;
  volatile unsigned char _val     = 0;

  for (_cindx = 0; _cindx < _size; ++_cindx)
    {
      _val     = _buff[_cindx];
      _read_op = !_read_op;

      _buff[_cindx] = _val;
      _read_op      = !_read_op;
    }
  return true;
}


bool
check_read_buff (const void* _sbuff, const unsigned int _size)
{
  return check_buff (const_cast<void*> (_sbuff), _size);
}

}}}      // namespace libs::helpers::mem
