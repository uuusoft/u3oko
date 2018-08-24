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

namespace dlls { namespace filter_noise { namespace space {
//  syn
using ::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp;
using ::libs::optim::s16bit::conv::base::c3x3::cores::TCore;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp;
using ::libs::ievents::props::videos::noises::space::ext::TypeSortAlg;
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::libs::helpers::statistic::ExpandedTimeStatistic;
using ::libs::helpers::statistic::helpers::functors::AddTimeStatistic;
using ::libs::helpers::statistic::helpers::functors::TStatLogger;
using ::libs::helpers::statistic::helpers::functors::TStatReset;
using ::libs::optim::mcalls::InfoMFunct;
using ::libs::optim::io::MCallInfo;
using ::libs::optim::io::ProxyBuff;
using ::libs::optim::mcalls::CallerImpl;

}}}      // namespace dlls::filter_noise::space
