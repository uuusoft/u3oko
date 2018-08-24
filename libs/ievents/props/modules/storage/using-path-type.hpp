//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       using-path-type.hpp
\date       22.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace storage {
/**
  \brief  Перечисление состояний в которых могут находится данные по данном пути.
  */
enum struct UsingPathType
{
  disabled,       //< Отключено, запрещен любой доступ.
  read_only,      //< Только для чтения.
  read_write      //< Произвольный доступ, запись/чтение.
};
/**
\brief  ???
*/
inline UsingPathType
str2using_path (const std::string& _str)
{
  /*threadlocal static*/ const std::unordered_map<std::string, UsingPathType> strs2paths = {
    { "", UsingPathType::disabled },
    { "disabled", UsingPathType::disabled },
    { "read_only", UsingPathType::read_only },
    { "read_write", UsingPathType::read_write }
  };

  auto _find = strs2paths.find (_str);
  if (strs2paths.end () == _find)
    {
      XULOG_WARNING ("failed convert str2using_path, " << _str);
      return UsingPathType::disabled;
    }
  return _find->second;
}

}}}}}      // namespace libs::ievents::props::modules::storage
