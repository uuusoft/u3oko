#pragma once
/**
\file       vgen-conv3_11-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       14.09.2018
\project    u3_vgen_conv
*/

namespace dlls::gens::vgen_conv3_11::syn
{
using VideoConvolutionProp     = ::libs::ievents::props::videos::generic::convolution::VideoConvolutionProp;
using BuffVideoConvolutionProp = ::libs::ievents::props::videos::generic::convolution::BuffVideoConvolutionProp;
using FilterInfo               = ::libs::icore::impl::var1::obj::FilterInfo;
using TransformInfo            = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo           = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;

namespace base = ::libs::optim::s16bit::conv::base;
}   // namespace dlls::gens::vgen_conv3_11::syn
