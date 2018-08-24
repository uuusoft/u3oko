//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       get_place_call_funct.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
/**
\brief      Функция для формирования текстового описания точки вызова (имя функции + номер строки).
\param[in]  _file имя файла.
\param[in]  _line номер строки.
\return     текстовое описание точки вызова.
*/
inline std::string
get_place_call (const char* _file = __FILE__, int _line = __LINE__)
{
  std::string _ret;

  _ret.reserve (2048);
  _ret += _file;
  _ret += ":";
  _ret += to_str (_line);
  return _ret;
}
