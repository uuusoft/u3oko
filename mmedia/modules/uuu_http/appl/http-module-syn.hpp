#pragma once
/**
\file       http-module-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_http_module
*/

namespace modules::uuu_http::appl::syn
{
using IEvent                       = ::libs::events::IEvent;
using ChangDShowRunsSubSysLogEvent = ::libs::ilog_events::events::ChangDShowRunsSubSysLogEvent;
using ChangeStateProcessEvent      = ::libs::ievents::runtime::state::ChangeStateProcessEvent;
using WrapperHttpEvent             = ::libs::ihttp_events::events::WrapperHttpEvent;
using ZipDataEvent                 = ::libs::ievents::runtime::mem::ZipDataEvent;
using RuntimeEvent                 = ::libs::ievents::runtime::RuntimeEvent;
using MemResourceHttpEvent         = ::libs::ihttp_events::events::MemResourceHttpEvent;
using IBlockMem                    = ::libs::helpers::mem::IBlockMem;
using Loader                       = ::libs::iproperties::xml::Loader;
using StateProcessEventExt         = ::libs::ilink::appl::StateProcessEventExt;
using ISystemProperty              = ::libs::iproperties::vers::system::ISystemProperty;
using IApplication                 = ::libs::link::appl::IApplication;
using InitApplication              = ::libs::link::appl::InitApplication;
using Calls                        = ::libs::link::details::Calls;
using CallSyncs                    = ::libs::link::details::CallSyncs;
using ILinksProperty               = ::libs::properties::vers::links::ILinksProperty;

namespace mids = ::libs::properties::vers::links::mids;
}   // namespace modules::uuu_http::appl::syn
