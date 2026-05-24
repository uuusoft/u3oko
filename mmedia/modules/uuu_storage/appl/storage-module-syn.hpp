#pragma once
/**
\file       storage-module-syn.hpp
\date       23.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_module_storage
*/

namespace modules::uuu_storage::appl::syn
{
using events_list_type           = std::list< ::libs::events::IEvent::ptr >;
using PropertyStorageModuleEvent = ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent;
using ChangeStateProcessEvent    = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using MemResourceStorageEvent    = ::libs::istorage_events::events::MemResourceStorageEvent;
using GetRuntimeInfo             = ::libs::istorage_events::events::GetRuntimeInfo;
using GetObjects                 = ::libs::istorage_events::events::GetObjects;
using GetStatisticInfo           = ::libs::istorage_events::events::GetStatisticInfo;
using UpdateStream               = ::libs::istorage_events::events::UpdateStream;
using WriteData                  = ::libs::istorage_events::events::WriteData;
using ReadData                   = ::libs::istorage_events::events::ReadData;
using StateProcessEventExt       = ::libs::ilink::appl::StateProcessEventExt;
}   // namespace modules::uuu_storage::appl::syn
