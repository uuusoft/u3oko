#pragma once
/**
\file       check_buff.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/

namespace libs { namespace helpers { namespace mem {
/*
  \brief  функия проверки блока памяти на чтение и запись
  */
bool check_buff (void* _buff, const unsigned int _size);
/*
  \brief  функия проверки блока памяти на чтение и запись
  */
bool check_read_buff (const void* _sbuff, const unsigned int _size);

}}}      // namespace libs::helpers::mem
