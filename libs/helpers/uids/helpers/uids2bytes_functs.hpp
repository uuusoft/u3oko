#pragma once
/**
\file       uids2bytes_functs.hpp
\brief      Некоторые вспомогтальные системыне функции
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2016.
\copyright  www.uuusoft.com
\project    uuu_helpers
*/

namespace libs { namespace helpers { namespace uids { namespace helpers {
/**
  \brief      Функция возращает число байт, на пиксель, которое соответствует данному формату
  \param[in]  _format   формат пикселей.
  \return     количество байт на пиксель.
  */
int get_count_bytes_from_format (const utils::cuuid& _format);
/**
  \brief      Функция возращает коэффициент масштабирования по вертикали, которое соответствует данному формату. 
              Т.к. ряд форматов хранят пиксели распределенно.
  \param[in]  _format   формат пикселей.
  \return     коэффициент масштабирования по вертикали.
  */
int get_hkoeff_from_format (const utils::cuuid& _format);
/**
  \brief      Функция возращает читаемое имя для известных форматов в виде guid.
  \param[in]  _format guid
  \return     текстовое представление guid.
  */
std::string get_readable_name (const utils::cuuid& _format);
/**
  \brief      Функция возращает признак сжатости форматов.
  \param[in]  _format guid
  \return     true, если формат не сжатый.
  */
bool is_raw_format (const utils::cuuid& _format);

}}}}      // namespace libs::helpers::uids::helpers
