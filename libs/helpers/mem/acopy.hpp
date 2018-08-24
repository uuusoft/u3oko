#pragma once
/**
\file       acopy.hpp
\date       25.08.2016
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      Обявление функции копирования блока памяти для всей системы.
*/

namespace libs { namespace helpers { namespace mem {
/*
  \brief  Функция копирования блока памяти. В отладочной версии используется ряд дополнительх проверок.
  */
void acopy (const void* _src, void* _dst, std::size_t _size);

}}}      // namespace libs::helpers::mem
