#pragma once
/**
\file       http-module-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    mhttp
*/

namespace modules::mhttp::appl::syn
{
using IEvent                    = ::libs::events::IEvent;
using ChangeStateSubSysLogEvent = ::libs::events_log::events::ChangeStateSubSysLogEvent;
using ChangeStateProcessEvent   = ::libs::events_base::runtime::state::ChangeStateProcessEvent;
using WrapperHttpEvent          = ::libs::events_http::events::WrapperHttpEvent;
using ZipDataEvent              = ::libs::events_base::runtime::mem::ZipDataEvent;
using RuntimeEvent              = ::libs::events_base::runtime::RuntimeEvent;
using MemResourceHttpEvent      = ::libs::events_http::events::MemResourceHttpEvent;
using IBlockMem                 = ::libs::utility::mem::IBlockMem;
using Loader                    = ::libs::iproperties::xml::Loader;
using StateProcessEventExt      = ::libs::ilink::appl::StateProcessEventExt;
using ISystemProperty           = ::libs::iproperties::vers::system::ISystemProperty;
using IApplication              = ::libs::link::appl::IApplication;
using InitApplication           = ::libs::link::appl::InitApplication;
using Calls                     = ::libs::link::details::Calls;
using CallSyncs                 = ::libs::link::details::CallSyncs;
using ILinksProperty            = ::libs::properties::vers::links::ILinksProperty;

namespace mids      = ::libs::properties::vers::links::mids;
namespace http      = ::boost::beast::http;
namespace websocket = ::boost::beast::websocket;
}   // namespace modules::mhttp::appl::syn
