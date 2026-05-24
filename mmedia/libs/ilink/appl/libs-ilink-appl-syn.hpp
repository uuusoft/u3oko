#pragma once
/**
\file       libs-ilink-appl-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_ilink
*/

namespace libs::ilink::appl::syn
{
using IEvent                       = ::libs::events::IEvent;
using ApplicationProp              = ::libs::ievents::props::application::ApplicationProp;
using InfoCPUEvent                 = ::libs::ievents::props::hardware::InfoCPUEvent;
using PropertyLogModuleEvent       = ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using PropertyStorageModuleEvent   = ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent;
using ChangeStateProcessEvent      = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using ChangDShowRunsSubSysLogEvent = ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent;
using TextExtCpu                   = ::libs::helpers::sys::cpu::TextExtCpu;
using LogVals                      = ::libs::ievents::props::modules::log::LogVals;
using ISharedProperty              = ::libs::properties::ISharedProperty;
using ISystemProperty              = ::libs::iproperties::vers::system::ISystemProperty;

namespace mids = libs::properties::vers::links::mids;
}   // namespace libs::ilink::appl::syn
