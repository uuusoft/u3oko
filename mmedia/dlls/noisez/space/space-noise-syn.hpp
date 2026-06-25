#pragma once
/**
\file       space-noise-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_filter_space
*/

namespace dlls::noisez::space::syn
{
using ISystemProperty            = ::libs::iproperties::vers::system::ISystemProperty;
using VideoSpaceNoiseRemoverProp = ::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp;
using MedianSpaceFilterProp      = ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp;
using Sortings                   = ::libs::ievents::props::videos::noises::space::ext::Sortings;
using ExpandedTimes              = ::libs::helpers::statistic::ExpandedTimes;
using IVideoBuf                  = ::utils::dbufs::video::IVideoBuf;
using TransformInfo              = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo             = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo                 = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo                = ::libs::icore::impl::var1::obj::ConnectInfo;
using ProxyBuf                   = ::libs::optim::io::ProxyBuf;
using IEvent                     = ::libs::events::IEvent;
using AddEvent2Base              = ::libs::ievents_events::events::AddEvent2Base;

namespace space_consts = ::libs::ievents::props::videos::noises::space::ext::consts;
namespace offs         = ::utils::dbufs::video::consts::offs;
}   // namespace dlls::noisez::space::syn
