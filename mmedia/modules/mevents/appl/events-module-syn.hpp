#pragma once
/**
\file       events-module-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mevents
*/

namespace modules::mevents::appl::syn
{
using ChangeStateProcessEvent   = ::libs::events_base::runtime::state::ChangeStateProcessEvent;
using AddEvent2EventsMsg        = ::libs::events_msg::events::AddEvent2EventsMsg;
using GetDataGraphsEventsMsg    = ::libs::events_msg::events::GetDataGraphsEventsMsg;
using UpdateListenerEventsMsg   = ::libs::events_msg::events::UpdateListenerEventsMsg;
using SubscribeActions          = ::libs::events_msg::events::SubscribeActions;
using OpsStatusEvent            = ::libs::events_base::OpsStatusEvent;
using ISystemProperty           = ::libs::iproperties::vers::system::ISystemProperty;
using ChangeStateSubSysLogEvent = ::libs::events_log::events::ChangeStateSubSysLogEvent;
using WrapperEventsEvent        = ::libs::events_msg::events::WrapperEventsEvent;
using GetEventsFromBase         = ::libs::events_msg::events::GetEventsFromBase;
using IEvent                    = ::libs::events::IEvent;
using StateProcessEventExt      = ::libs::ilink::appl::StateProcessEventExt;
using IApplication              = ::libs::link::appl::IApplication;
using InitApplication           = ::libs::link::appl::InitApplication;
using Calls                     = ::libs::link::details::Calls;
using CallSyncs                 = ::libs::link::details::CallSyncs;
using ILinksProperty            = ::libs::properties::vers::links::ILinksProperty;
}   // namespace modules::mevents::appl::syn
