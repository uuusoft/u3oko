#pragma once
/**
\file       log-module-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_module_log
*/

namespace modules::uuu_log::appl::syn
{
using events_list_type             = std::list< ::libs::events::IEvent::ptr >;
using list_folders_type            = ::libs::ilog_events::events::ProcessListLogsEvent::list_folders_type;
using InfoLogEvent                 = ::libs::ilog_events::events::InfoLogEvent;
using PropertyLogModuleEvent       = ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using ChangeStateProcessEvent      = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using ChangDShowRunsSubSysLogEvent = ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent;
using ProcessListLogsEvent         = ::libs::ilog_events::events::ProcessListLogsEvent;
using ProcessLogEvent              = ::libs::ilog_events::events::ProcessLogEvent;
using InfoLogSession               = ::libs::ilog_events::events::InfoLogSession;
using suppressor_type              = ::libs::helpers::log::SupressorVerboseLogMsg< ::libs::events::IEvent::ptr, libs::helpers::thread::EmptyMutex >;
using LogVals                      = ::libs::ievents::props::modules::log::LogVals;
using IEvent                       = ::libs::events::IEvent;
using StateProcessEventExt         = ::libs::ilink::appl::StateProcessEventExt;
}   // namespace modules::uuu_log::appl::syn
