#pragma once
/**
\file       dbufs-is-valid-helpers-funcs.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\brief      Функция проверки корректности типа-индекса назначание буфера
*/

namespace utils::dbufs::video::consts::offs
{
/// Функция проверки корректности типа-индекса буфера
/// \param[in]  indx индекс буфера
/// \return     true, если индекс корректен, иначе false
inline bool
is_valid (const off_buf_type indx)
{
  return invalid != indx ? true : false;
}
}   // namespace utils::dbufs::video::consts::offs
