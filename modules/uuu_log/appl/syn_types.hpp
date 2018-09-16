//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_log
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace modules { namespace uuu_log { namespace appl {

using ::libs::ilog_events::events::BaseLogEvent;
using ::libs::ilog_events::events::InfoLogEvent;
using ::libs::ilink::LinkCreatorProxy;
using ::libs::link::details::RunCodeType;
using ::libs::link::ILink;
using ::libs::events::IEvent;
using ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using ::libs::ievents::props::modules::log::ValsLogModule;
using ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using ::libs::ievents::runtime::state::ChangStateProcessTypeEvent;
using ::libs::ilog_events::events::ProcessListLogsEvent;
using ::libs::ilog_events::events::InfoLogEvent;
using ::libs::ilog_events::events::ProcessLogEvent;
using ::libs::helpers::files::NodeEnumFiles;
using ::libs::ilog_events::events::ProcessLogEvent;

using list_folders_type = ProcessListLogsEvent::list_folders_type;
using info_session_type = ProcessLogEvent::info_session_type;
using events_list_type  = std::list<::libs::events::IEvent::ptr>;

namespace bip     = ::boost::interprocess;
namespace bfs     = ::boost::filesystem;
namespace bss     = boost::system;
namespace eevents = ::libs::events;
namespace ievents = ::libs::ievents_events::events;
namespace revents = ::libs::ievents::runtime;
namespace mevents = ::libs::ievents::props::modules;
namespace levents = ::libs::ilog_events::events;

}}}      // namespace modules::uuu_log::appl
