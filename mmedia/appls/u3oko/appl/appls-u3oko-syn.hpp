#pragma once
/**
\file       appls-u3oko-syn.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3oko
*/

namespace appls::u3oko::appl::syn
{
using CommandCodeEvent        = ::libs::igui_events::events::CommandCodeEvent;
using FrameDone               = ::libs::ievents::runtime::video::FrameDone;
using ChangeStateProcessEvent = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using IEvent                  = ::libs::events::IEvent;
using InitApplication         = ::libs::link::appl::InitApplication;
using StateProcessEventExt    = ::libs::ilink::appl::StateProcessEventExt;
using CallSyncs               = ::libs::link::details::CallSyncs;
using Calls                   = ::libs::link::details::Calls;

namespace mids = libs::properties::vers::links::mids;
}   // namespace appls::u3oko::appl::syn
