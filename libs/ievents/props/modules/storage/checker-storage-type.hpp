//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       checker-storage-type.hpp
\date       15.08.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace storage {
/**
\brief  Перечисление состояний в которых могут находится данные по данном пути.
*/
enum struct CheckerStorageType
{
  disabled,                        //< Отключены все проверки.
  start_stop,                      //< Проверка только после запуска и сразу после остановки. По умолчанию.
  periodicaly,                     //< Периодически, через заданный интервал времени.
  after_every_write_operation      //< После каждой операции записи. Для отладки.
};
/**
\brief  ???
*/
inline CheckerStorageType
str2checker_storage (const std::string& _str)
{
  /*threadlocal static*/ const std::unordered_map<std::string, CheckerStorageType> strs2checkers = {
    { "", CheckerStorageType::start_stop },
    { "start_stop", CheckerStorageType::start_stop },
    { "disabled", CheckerStorageType::disabled },
    { "periodicaly", CheckerStorageType::periodicaly },
    { "after_every_write_operation", CheckerStorageType::after_every_write_operation }
  };

  auto _find = strs2checkers.find (_str);
  if (strs2checkers.end () == _find)
    {
      XULOG_WARNING ("failed convert str2checker_storage, " << _str);
      return CheckerStorageType::start_stop;
    }
  return _find->second;
}

}}}}}      // namespace libs::ievents::props::modules::storage
