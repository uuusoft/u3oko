#pragma once
/**
\file       data-module-syn.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_module_data
*/

namespace modules::uuu_mdata::appl::syn
{
using ListDevicesDataEvent         = ::libs::imdata_events::events::ListDevicesDataEvent;
using ChangeGraphsDataEvent        = ::libs::imdata_events::events::ChangeGraphsDataEvent;
using ListXmlFilesDataEvent        = ::libs::imdata_events::events::ListXmlFilesDataEvent;
using GetNodesDataEvent            = ::libs::imdata_events::events::GetNodesDataEvent;
using ChangeNodeDataEvent          = ::libs::imdata_events::events::ChangeNodeDataEvent;
using GraphActions                 = ::libs::imdata_events::events::GraphActions;
using ExpandTimesEvent             = ::libs::ievents::runtime::state::ExpandTimesEvent;
using ChangDShowRunsSubSysLogEvent = ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent;
using ChangeStateProcessEvent      = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using CommandCodeEvent             = ::libs::igui_events::events::CommandCodeEvent;
using InfoCPUEvent                 = ::libs::ievents::props::hardware::InfoCPUEvent;
using NodeID                       = ::libs::core::graph::NodeID;
using IEvent                       = ::libs::events::IEvent;
using ISystemProperty              = ::libs::iproperties::vers::system::ISystemProperty;
using ILinksProperty               = ::libs::properties::vers::links::ILinksProperty;
using NodeEnumFiles                = ::libs::helpers::files::NodeEnumFiles;
using GraphStates                  = ::libs::core::graph::GraphStates;
using StateProcessEventExt         = ::libs::ilink::appl::StateProcessEventExt;
using InitLoaderInfo               = ::libs::iproperties::xml::InitLoaderInfo;
using Loader                       = ::libs::iproperties::xml::Loader;
using Paths                        = ::libs::iproperties::appl_paths::Paths;
}   // namespace modules::uuu_mdata::appl::syn
