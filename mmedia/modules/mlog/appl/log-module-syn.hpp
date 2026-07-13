#pragma once
/**
\file       log-module-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mlog
*/

namespace modules::mlog::appl::syn
{
using events_list_type          = std::list< ::libs::events::IEvent::ptr >;
using list_folders_type         = ::libs::events_log::events::ProcessListLogsEvent::list_folders_type;
using InfoLogEvent              = ::libs::events_log::events::InfoLogEvent;
using PropertyLogModuleEvent    = ::libs::events_base::props::modules::log::PropertyLogModuleEvent;
using ChangeStateProcessEvent   = ::libs::events_base::runtime::state::ChangeStateProcessEvent;
using ChangeStateSubSysLogEvent = ::libs::events_log::events::ChangeStateSubSysLogEvent;
using ProcessListLogsEvent      = ::libs::events_log::events::ProcessListLogsEvent;
using ProcessLogEvent           = ::libs::events_log::events::ProcessLogEvent;
using InfoLogSession            = ::libs::events_log::events::InfoLogSession;
using suppressor_type           = ::libs::utility::log::SupressorVerboseLogMsg< ::libs::events::IEvent::ptr, libs::utility::thread::EmptyMutex >;
using LogVals                   = ::libs::events_base::props::modules::log::LogVals;
using IEvent                    = ::libs::events::IEvent;
using StateProcessEventExt      = ::libs::ilink::appl::StateProcessEventExt;

namespace mids = ::libs::properties::vers::links::mids;
}   // namespace modules::mlog::appl::syn
