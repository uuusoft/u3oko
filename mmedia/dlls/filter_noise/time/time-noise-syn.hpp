#pragma once
/**
\file       time-noise-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_time_filter_noise
*/

namespace dlls::filter_noise::time::syn
{
using VideoTimeNoiseRemoverProp = ::libs::ievents::props::videos::noises::time::VideoTimeNoiseRemoverProp;
using MedianTimeFilterProp      = ::libs::ievents::props::videos::noises::time::ext::MedianTimeFilterProp;
using TStatLogger               = ::libs::helpers::statistic::helpers::functors::TStatLogger;
using AddOpTime                 = ::libs::helpers::statistic::helpers::functors::AddOpTime;
using TransformInfo             = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ExpandedTimes             = ::libs::helpers::statistic::ExpandedTimes;
}   // namespace dlls::filter_noise::time::syn
