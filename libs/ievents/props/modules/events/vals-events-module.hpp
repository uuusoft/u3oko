//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       vals-events-module.hpp
\date       14.09.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ievents
\brief      empty brief
*/

namespace libs { namespace ievents { namespace props { namespace modules { namespace events {
/**
\brief  “ип дл€ перечислени€ различных полей дл€ модул€ хранени€ событий.
*/
enum struct ValsEventsModule
{
  max_count_events  = 0,       //< ћаксимальное количество хранимых сообщений.
  max_size_database = 1,       //< ћаксимальный размер базы данных в MB.
  no_val            = 15,      //< Ќе определено, дл€ общности. »спользуетс€ как сигнал отсутстви€ пол€.
  max_val           = 16       //< √раница значений данного типа дл€ формировани€ статических массивов, проверки значени€ и т.п..
};
/**
\brief  ???
*/
inline std::string
val2str (const ValsEventsModule& _val)
{
  /*thread_local static*/ const std::unordered_map<ValsEventsModule, std::string> _val2str = {
    { ValsEventsModule::max_count_events, consts::max_count_events },
    { ValsEventsModule::max_size_database, consts::max_size_database }
  };

  auto _find = _val2str.find (_val);
  if (_val2str.end () == _find)
    {
      XULOG_WARNING ("failed convert ValsEventsModule to string" << UUU_ICAST_INT (_val));
      return "";
    }
  return _find->second;
}
/**
\brief  ???
*/
inline ValsEventsModule
str2val (const std::string& _str)
{
  /*thread_local static*/ const std::map<std::string, ValsEventsModule> _str2val = {
    { consts::max_count_events, ValsEventsModule::max_count_events },
    { consts::max_size_database, ValsEventsModule::max_size_database }
  };

  auto _find = _str2val.find (_str);
  if (_str2val.end () == _find)
    {
      XULOG_WARNING ("failed convert string to ValsEventsModule, " << _str);
      return ValsEventsModule::no_val;
    }
  return _find->second;
}

}}}}}      // namespace libs::ievents::props::modules::events

#if 0
namespace std {
/**
\brief  ???
*/
template <>
struct hash<::libs::ievents::props::modules::events::ValsEventsModule>
{
  size_t
  operator() (const ::libs::ievents::props::modules::events::ValsEventsModule& _val) const noexcept
  {
    return UUU_ICAST_SIZE_T (_val);
  }
};

}      // namespace std
#endif
