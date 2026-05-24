#pragma once
/**
\file       dbufs-is-valid-helpers-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_dbufs
\brief      Функция проверки корректности типа-индекса назначание буфера
*/

namespace utils::dbufs::video::consts::offs
{
/// Функция проверки корректности типа-индекса буфера
/// \param[in]  _indx индекс буфера
/// \return     true, если индекс корректен, иначе false
inline bool
is_valid (const off_buf_type& _indx)
{
  return invalid != _indx ? true : false;
}
}   // namespace utils::dbufs::video::consts::offs
