//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_icore
\brief      ќбъ€вление сокращенных синонимов дл€ всего данного модул€.
*/

namespace libs { namespace icore { namespace impl { namespace var1 { namespace path {
//  syn
using ::libs::helpers::statistic::ExpandedTimeStatistic;
using ::libs::helpers::statistic::helpers::functors::AddTimeStatistic;
using ::libs::optim::mcalls::CallerImpl;
using ::libs::core::path::PathObjID;
using ::libs::core::path::send_funct_type;
using ::libs::events::IEvent;
using ::libs::ievents::runtime::mem::BuffsEvent;
using ::libs::iproperties::appl_paths::TypePath;

namespace sruntime = ::libs::ievents::runtime;
namespace sprops   = ::libs::ievents::props;

}}}}}      // namespace libs::icore::impl::var1::path
