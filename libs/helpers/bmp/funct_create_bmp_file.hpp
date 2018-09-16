#pragma once
/**
\file       funct_create_bmp_file.hpp
\brief      Дополнительные функции
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief      empty brief
*/
//old shit
namespace libs { namespace helpers { namespace bmp {
#if 0
  /**
  \brief  Функция создает образ файла БМП в памяти, вызывающий должен освободить память образа
  \brief  после того как скинет файл на диск фукнцией ::base_functs::mem::afree
  */
  HRESULT CreateImageBMPFile (
    base_functs::mem::CCharBlock& image,
    const unsigned char*    data,
    int             size_data,
    AM_MEDIA_TYPE       info );
  /**
  \brief  то-же самое, только формирует кадр формата 4х3 и печатает сообщение, если нужно
  */
  HRESULT CreateImageBMPFile4x3 (
    base_functs::mem::CCharBlock& image,
    const unsigned char*    data,
    int             size_data,
    AM_MEDIA_TYPE       info,
    const std::string&      add_text,
    float           k_mull);
  /**
  \brief
  */
  HRESULT CreateImageBMPFile4x3 (
    base_functs::mem::CCharBlock& image,
    const unsigned char*    data,
    int             size_data,
    cuuid           subtype,
    int             width,
    int             height,
    const tstring&        add_text,
    float           k_mull);
  /**
  \brief  функция создает DIB RGB24 секцию на основе переданного изображения, при необходимости выделяется память
  */
  HRESULT CreateImageBMPFile2 (
    base_functs::mem::CCharBlock& image,
    const unsigned char*    data,
    int             size_data,
    cuuid           type_data,
    int             width,
    int             height,
    bool            need_dib_section);
#endif
}}}      // namespace libs::helpers::bmp
