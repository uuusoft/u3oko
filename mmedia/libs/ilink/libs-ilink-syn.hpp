#pragma once
/**
\file       libs-ilink-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::syn
{
using ISharedProperty = ::libs::properties::ISharedProperty;
using ISystemProperty = ::libs::iproperties::vers::system::ISystemProperty;
using IMem            = ::libs::link::mem::IMem;
using IEvent          = ::libs::events::IEvent;
using CodeRuns        = ::libs::link::details::CodeRuns;
using CallSyncs       = ::libs::link::details::CallSyncs;
using Calls           = ::libs::link::details::Calls;
using CallState       = ::libs::link::CallState;
using CreateInfo      = ::libs::link::CreateInfo;

namespace text = ::libs::link::consts::text;
}   // namespace libs::ilink::syn
