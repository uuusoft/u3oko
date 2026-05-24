#pragma once
/**
\file       libs-icore-impl-var1-graph-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_icore_lib
*/

namespace libs::icore::impl::var1::graph::syn
{
using IEvent          = ::libs::events::IEvent;
using ExpandedTimes   = ::libs::helpers::statistic::ExpandedTimes;
using AddOpTime       = ::libs::helpers::statistic::helpers::functors::AddOpTime;
using ISystemProperty = ::libs::iproperties::vers::system::ISystemProperty;
using ISharedProperty = ::libs::properties::ISharedProperty;
using ILinksProperty  = ::libs::properties::vers::links::ILinksProperty;
using NodeID          = ::libs::core::graph::NodeID;
using BaseInterfEvent = ::libs::ievents::runtime::interf::BaseInterfEvent;
using BufsEvent       = ::libs::ievents::runtime::mem::BufsEvent;
}   // namespace libs::icore::impl::var1::graph::syn
