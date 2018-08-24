#pragma once
/**
\file       defines_string2obj.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_defines
\brief      Объявление набора функций для конвертации типов в строку и обратно.
*/
#include "defines_tstring.hpp"

template <
  typename TTObject>
inline void
to_obj (const tstring& _str, TTObject& _obj)
{
  tstringstream _stream;

  _stream << _str;
  _stream >> _obj;
  return;
}


template <
  typename TTObject>
inline void
cto_obj (const std::string& _str, TTObject& _obj)
{
  std::stringstream _temp;

  _temp << _str;
  _temp >> _obj;
  return;
}


template <>
inline void
to_obj (const tstring& _str, tstring& _obj)
{
  _obj = _str;
  return;
}


template <
  typename TTObject>
inline tstring
to_strw (const TTObject& _obj)
{
  tstring       _str;
  tstringstream _stream;

  _stream << _obj;
  _stream >> _str;
  return _str;
}


template <
  typename TTObject>
inline std::string
to_str (const TTObject& _obj)
{
  std::string       _str;
  std::stringstream _stream;

  _stream << _obj;
  _stream >> _str;
  return _str;
}


template <>
inline tstring
to_strw (const tstring& _obj)
{
  return _obj;
}
