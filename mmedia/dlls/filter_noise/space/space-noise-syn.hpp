#pragma once
/**
\file       space-noise-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_filter_space
*/

namespace dlls::filter_noise::space::syn
{
using VideoSpaceNoiseRemoverProp = ::libs::ievents::props::videos::noises::space::VideoSpaceNoiseRemoverProp;
using MedianSpaceFilterProp      = ::libs::ievents::props::videos::noises::space::ext::MedianSpaceFilterProp;
using TransformInfo              = ::libs::icore::impl::var1::obj::dll::TransformInfo;
}   // namespace dlls::filter_noise::space::syn
