//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.05.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_module_data
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace modules { namespace uuu_mdata { namespace appl {
//  syn
using ::libs::events::IEvent;
using ::libs::link::details::TypeRunCode;
using ::libs::ilink::LinkCreatorProxy;
using ::libs::properties::ISharedProperty;
using ::libs::link::ILink;
using ::libs::helpers::files::NodeEnumFiles;
using ::libs::optim::io::TInit;
using ::libs::ievents::props::hardware::InfoCPUEvent;
using ::libs::ievents::runtime::video::FrameDone;
using ::libs::imdata_events::events::ChangePathsDataEvent;
using ::libs::imdata_events::events::ListDevicesDataEvent;
using ::libs::imdata_events::events::ListXmlFilesDataEvent;
using ::libs::imdata_events::events::GetNodesDataEvent;
using ::libs::imdata_events::events::ChangeNodeDataEvent;
using ::libs::ievents::runtime::state::ExpandTimeStatisticEvent;

namespace bip     = boost::interprocess;
namespace revents = ::libs::ievents::runtime;
//namespace mevents = ::libs::imdata_events::events;

}}}      // namespace modules::uuu_mdata::appl
