#pragma once
/**
\file       func_create_bmp_file.hpp
\brief      Дополнительные функции
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2016
\project    u3_helpers_lib
*/

// old shit
namespace libs::helpers::bmp
{
#ifdef U3_FAKE_DISABLE
/// Функция создает образ файла БМП в памяти, вызывающий должен освободить память образа
// после того как скинет файл на диск фукнцией ::base_funcs::mem::afree
HRESULT CreateImageBMPFile (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  AM_MEDIA_TYPE                info);

/// то-же самое, только формирует кадр формата 4х3 и печатает сообщение, если нужно
HRESULT CreateImageBMPFile4x3 (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  AM_MEDIA_TYPE                info,
  const std::string&           add_text,
  float                        k_mull);

HRESULT CreateImageBMPFile4x3 (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  cuuid                        subtype,
  int                          width,
  int                          height,
  const tstring&               add_text,
  float                        k_mull);

/// функция создает DIB RGB24 секцию на основе переданного изображения, при необходимости выделяется память
HRESULT CreateImageBMPFile2 (
  base_funcs::mem::CCharBlock& image,
  const std::uint8_t*          data,
  int                          size_data,
  cuuid                        type_data,
  int                          width,
  int                          height,
  bool                         need_dib_section);
#endif
}   // namespace libs::helpers::bmp
