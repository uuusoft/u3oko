//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_unknown
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace modules { namespace uuu_events { namespace appl {
//  syn
using ::libs::events::IEvent;
using ::libs::ilog_events::events::BaseLogEvent;
using ::libs::ilink::LinkCreatorProxy;
using ::libs::link::details::RunCodeType;
using ::libs::link::appl::InitApplication;
using ::libs::link::ILink;
using ::libs::ievents_events::events::WrapperEventsEvent;
using ::libs::ievents_events::events::AddEvent2Base;
using ::libs::ievents::runtime::state::ChangStateProcessTypeEvent;

namespace bip     = boost::interprocess;
namespace eevents = ::libs::events;
namespace ievents = ::libs::ievents_events::events;
namespace revents = ::libs::ievents::runtime;

}}}      // namespace modules::uuu_events::appl
