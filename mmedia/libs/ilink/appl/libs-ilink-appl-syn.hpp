#pragma once
/**
\file       libs-ilink-appl-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_ilink
*/

namespace libs::ilink::appl::syn
{
using IEvent                     = ::libs::events::IEvent;
using ApplicationProp            = ::libs::ievents::props::application::ApplicationProp;
using InfoCPUEvent               = ::libs::ievents::props::hardware::InfoCPUEvent;
using PropertyLogModuleEvent     = ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using PropertyStorageModuleEvent = ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent;
using ChangeStateProcessEvent    = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using ChangeStateSubSysLogEvent  = ::libs::ilog_events::events::ChangeStateSubSysLogEvent;
using WrapperEventsEvent         = ::libs::ievents_events::events::WrapperEventsEvent;
using ExpandTimesEvent           = ::libs::ievents::runtime::state::ExpandTimesEvent;
using TextExtCpu                 = ::libs::helpers::sys::cpu::TextExtCpu;
using LogVals                    = ::libs::ievents::props::modules::log::LogVals;
using ISharedProperty            = ::libs::properties::ISharedProperty;
using ISystemProperty            = ::libs::iproperties::vers::system::ISystemProperty;
using IAppPaths                  = ::libs::iproperties::appl_paths::IAppPaths;
using BlockMemAllocatorProxy     = ::utils::mem_funcs::impl::BlockMemAllocatorProxy;
using BufAllocatorProxy          = ::utils::dbufs::allocator::BufAllocatorProxy;
using id_link_type               = ::libs::ievents::props::base_id::id_link_type;
using ILinksProperty             = ::libs::properties::vers::links::ILinksProperty;

namespace mids = libs::properties::vers::links::mids;
namespace log  = ::libs::ievents::props::modules::log;
}   // namespace libs::ilink::appl::syn
