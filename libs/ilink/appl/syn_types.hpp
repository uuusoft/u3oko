//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_ilink
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace libs { namespace ilink { namespace appl {
//  syn
using ::libs::ievents::props::application::ApplicationProp;
using ::libs::ievents::props::hardware::InfoCPUEvent;
using ::libs::ievents::props::modules::log::PropertyLogModuleEvent;
using ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent;
using ::libs::events::IEvent;
using ::libs::igui_events::events::CommandCodeEvent;
using ::libs::iproperties::vers::system::ISystemProperty;
using ::libs::iproperties::vers::demon::IDemonsProperty;
using ::libs::iproperties::appl_paths::IAppPaths;
using ::libs::iproperties::appl_paths::TypePath;
using ::utils::mem_functs::impl::BlockMemAllocatorProxy;
using ::utils::dbuffs::allocator::BuffAllocatorProxy;
using ::libs::optim::io::IOptimProxy;
using ::libs::helpers::sys::ISysInfo;
using ::libs::helpers::sys::cpu::CpuInfo;
using ::libs::events::io::IEventsProxy;
using ::libs::link::ILink;

namespace bip     = boost::interprocess;
namespace revents = ::libs::ievents::runtime;
namespace mevents = ::libs::imdata_events::events;

}}}      // namespace libs::ilink::appl
