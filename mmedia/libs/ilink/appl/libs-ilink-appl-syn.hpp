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
using ApplicationProp            = ::libs::events_base::props::application::ApplicationProp;
using InfoCPUEvent               = ::libs::events_base::props::hardware::InfoCPUEvent;
using PropertyLogModuleEvent     = ::libs::events_base::props::modules::log::PropertyLogModuleEvent;
using PropertyStorageModuleEvent = ::libs::events_base::props::modules::storage::PropertyStorageModuleEvent;
using ChangeStateProcessEvent    = ::libs::events_base::runtime::state::ChangeStateProcessEvent;
using ChangeStateSubSysLogEvent  = ::libs::events_log::events::ChangeStateSubSysLogEvent;
using WrapperEventsEvent         = ::libs::events_msg::events::WrapperEventsEvent;
using ExpandTimesEvent           = ::libs::events_base::runtime::state::ExpandTimesEvent;
using TextExtCpu                 = ::libs::utility::sys::cpu::TextExtCpu;
using LogVals                    = ::libs::events_base::props::modules::log::LogVals;
using ISharedProperty            = ::libs::properties::ISharedProperty;
using ISystemProperty            = ::libs::iproperties::vers::system::ISystemProperty;
using IAppPaths                  = ::libs::iproperties::appl_paths::IAppPaths;
using BlockMemAllocatorProxy     = ::utils::mem_funcs::impl::BlockMemAllocatorProxy;
using BufAllocatorProxy          = ::utils::dbufs::allocator::BufAllocatorProxy;
using id_link_type               = ::libs::events_base::props::base_id::id_link_type;
using ILinksProperty             = ::libs::properties::vers::links::ILinksProperty;

namespace mids = libs::properties::vers::links::mids;
namespace log  = ::libs::events_base::props::modules::log;
}   // namespace libs::ilink::appl::syn
