#pragma once
/**
\file       events-module-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_module_events
*/

namespace modules::u3_events::appl::syn
{
using ChangeStateProcessEvent      = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using AddEvent2Base                = ::libs::ievents_events::events::AddEvent2Base;
using GetDataGraphsFromEventBase   = ::libs::ievents_events::events::GetDataGraphsFromEventBase;
using UpdateListener               = ::libs::ievents_events::events::UpdateListener;
using SubscribeActions             = ::libs::ievents_events::events::SubscribeActions;
using ISystemProperty              = ::libs::iproperties::vers::system::ISystemProperty;
using ChangDShowRunsSubSysLogEvent = ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent;
using WrapperEventsEvent           = ::libs::ievents_events::events::WrapperEventsEvent;
using IEvent                       = ::libs::events::IEvent;
using StateProcessEventExt         = ::libs::ilink::appl::StateProcessEventExt;
using IApplication                 = ::libs::link::appl::IApplication;
using InitApplication              = ::libs::link::appl::InitApplication;
using Calls                        = ::libs::link::details::Calls;
using CallSyncs                    = ::libs::link::details::CallSyncs;
using ILinksProperty               = ::libs::properties::vers::links::ILinksProperty;
}   // namespace modules::u3_events::appl::syn
