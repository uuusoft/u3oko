//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    u3oko
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

/// ѕространство имен дл€ модулей "приложение". “.е. фактически дл€ "моделей и контроллеров".
namespace appls {
/// ѕространство имен дл€ приложение "тестирование".
namespace u3oko {
/// ѕространство имен дл€ основного модул€ приложени€.
namespace appl {
//  syn
using ::libs::events::IEvent;
using ::libs::igui_events::events::CommandCodeEvent;
using ::libs::imdata_events::events::ChangePathsDataEvent;
using ::libs::link::details::RunCodeType;
using ::libs::link::appl::InitApplication;
using ::libs::iproperties::appl_paths::TypePath;
using ::libs::ilink::LinkCreatorProxy;
using ::libs::link::ILink;
using ::boost::posix_time::ptime;
using ::boost::posix_time::time_duration;

}      // namespace appl
}      // namespace u3oko
}      // namespace appls
