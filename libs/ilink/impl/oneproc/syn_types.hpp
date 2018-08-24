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

namespace libs { namespace ilink { namespace impl { namespace oneproc {
//  syn
using ::libs::events::IEvent;
using ::libs::events::ISeqEvent;
using ::libs::link::CreateInfo;
using ::libs::link::StateProcessEvent;
using ::libs::link::ILink;
using ::libs::helpers::hboost::NameRemover;
using ::libs::link::details::TypeSyncCall;
using ::libs::link::details::TypeRequestCall;
using ::libs::link::mem::IBlockMem;
using ::libs::link::mem::IHandlerMem;
using ::libs::link::details::TypeLinkModules;
using ::libs::link::TypeDestroyLink;

namespace bip = boost::interprocess;

}}}}      // namespace libs::ilink::impl::oneproc
