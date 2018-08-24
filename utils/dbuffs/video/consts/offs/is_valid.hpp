//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       is_valid.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_dbuffs
\brief      Функция проверки корректности типа-индекса назначание буфера.
*/

namespace utils { namespace dbuffs { namespace video { namespace consts { namespace offs {
/**
  \brief      Функция проверки корректности типа-индекса буфера.
  \param[in]  _indx индекс буфера.
  \return     true, если индекс корректен, иначе false.
  */
inline bool
is_valid (const off_buff_type& _indx)
{
  return invalid != _indx ? true : false;
}

}}}}}      // namespace utils::dbuffs::video::consts::offs
