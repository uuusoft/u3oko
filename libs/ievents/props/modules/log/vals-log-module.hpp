//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       vals-log-module.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace log {
/**
\brief  Тип для перечисления различных полей для модуля логирования.
*/
enum struct ValsLogModule
{
  max_cache_events           = 0,       //< Максимальное количество кешируемых сообщений в ожидании записи на носитель.
  ms_max_period_flush_events = 1,       //< Максимальный период кеширования сообщений в ожидании записи на носитель.
  max_size_one_log_file_byte = 2,       //< Максимальный размер одного файла логирования в байтах.
  enable_store_call_place    = 3,       //< Флаг, контролирует фиксацию в файле место вызова (файл/функция/строка) функции логирования.
  no_val                     = 15,      //< Не определено, для общности. Используется как сигнал отсутствия поля.
  max_val                    = 16       //< Граница значений данного типа для формирования статических массивов, проверки значения и т.п..
};
/**
\brief  ???
*/
inline std::string
val2str (const ValsLogModule& _val)
{
  /*thread_local static*/ const std::unordered_map<ValsLogModule, std::string> _val2str = {
    { ValsLogModule::max_cache_events, consts::max_cache_events },
    { ValsLogModule::ms_max_period_flush_events, consts::ms_max_period_flush_events },
    { ValsLogModule::max_size_one_log_file_byte, consts::max_size_one_log_file_byte },
    { ValsLogModule::enable_store_call_place, consts::enable_store_call_place }
  };

  auto _find = _val2str.find (_val);
  if (_val2str.end () == _find)
    {
      XULOG_WARNING ("failed convert ValsLogModule to string" << UUU_ICAST_INT (_val));
      return "";
    }
  return _find->second;
}
/**
\brief  ???
*/
inline ValsLogModule
str2val (const std::string& _str)
{
  /*thread_local static*/ const std::map<std::string, ValsLogModule> _str2val = {
    { consts::max_cache_events, ValsLogModule::max_cache_events },
    { consts::ms_max_period_flush_events, ValsLogModule::ms_max_period_flush_events },
    { consts::max_size_one_log_file_byte, ValsLogModule::max_size_one_log_file_byte },
    { consts::enable_store_call_place, ValsLogModule::enable_store_call_place }
  };

  auto _find = _str2val.find (_str);
  if (_str2val.end () == _find)
    {
      XULOG_WARNING ("failed convert string to ValsLogModule, " << _str);
      return ValsLogModule::no_val;
    }
  return _find->second;
}

}}}}}      // namespace libs::ievents::props::modules::log

#if 0
namespace std {
/**
\brief  ???
*/
template <>
struct hash<::libs::ievents::props::modules::log::ValsLogModule>
{
  size_t
  operator() (const ::libs::ievents::props::modules::log::ValsLogModule& _val) const noexcept
  {
    return UUU_ICAST_SIZE_T (_val);
  }
};

}      // namespace std
#endif
