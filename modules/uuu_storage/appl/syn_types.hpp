//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       23.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_storage
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace modules { namespace uuu_storage { namespace appl {

namespace bip     = ::boost::interprocess;
namespace bfs     = ::boost::filesystem;
namespace bss     = boost::system;
namespace eevents = ::libs::events;
namespace ievents = ::libs::ievents_events::events;
namespace revents = ::libs::ievents::runtime;
namespace mevents = ::libs::ievents::props::modules;
namespace levents = ::libs::ilog_events::events;
namespace sevents = ::libs::istorage_events::events;

using ::libs::events::IEvent;
using ::libs::istorage_events::stream_id_type;
using ::libs::istorage_events::TypeObjectId;
using ::libs::istorage_events::TypeActionStream;
using ::libs::istorage_events::TypeUpdateStream;
using ::libs::istorage_events::events::BaseStorageEvent;
using ::libs::istorage_events::events::WrapperStorageEvent;
using ::libs::istorage_events::events::MemResourceStorageEvent;
using ::libs::istorage_events::events::GetRuntimeInfo;
using ::libs::istorage_events::events::RuntimeStreamInfo;
using ::libs::istorage_events::events::GetObjects;
using ::libs::istorage_events::events::GetStatisticInfo;
using ::libs::istorage_events::events::ReadData;
using ::libs::istorage_events::events::WriteData;
using ::libs::istorage_events::events::UpdateStream;
using ::libs::ilink::LinkCreatorProxy;
using ::libs::link::details::TypeRunCode;
using ::libs::link::ILink;
using ::libs::helpers::files::NodeEnumFiles;
using ::utils::dbuffs::video::IVideoBuff;
using ::utils::dbuffs::IMemBuff;
using events_list_type = std::list<::libs::events::IEvent::ptr>;
using ::libs::ievents::props::modules::storage::PropertyStorageModuleEvent;
using ::libs::ievents::props::modules::storage::PathInfo;

}}}      // namespace modules::uuu_storage::appl
