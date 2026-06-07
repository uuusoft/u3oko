#pragma once
/**
\file       space-noise-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::noisez::space::syn
{
using ISystemProperty            = ::libs::iproperties::vers::system::ISystemProperty;
using VideoSpaceNoiseRemoverProp = ::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp;
using MedianSpaceFilterProp      = ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp;
using TransformInfo              = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo             = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ConnectInfo                = ::libs::icore::impl::var1::obj::ConnectInfo;
using Sortings                   = ::libs::ievents::props::videos::noises::space::ext::Sortings;
using ExpandedTimes              = ::libs::helpers::statistic::ExpandedTimes;
using IVideoBuf                  = ::utils::dbufs::video::IVideoBuf;

namespace space_consts = ::libs::ievents::props::videos::noises::space::ext::consts;
namespace offs         = ::utils::dbufs::video::consts::offs;
}   // namespace dlls::noisez::space::syn
