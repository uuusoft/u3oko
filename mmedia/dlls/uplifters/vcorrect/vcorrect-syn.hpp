#pragma once
/**
\file       vcorrect-syn.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect::syn
{
using VideoCorrectProp        = ::libs::ievents::props::videos::generic::correct::VideoCorrectProp;
using ICorrectImage           = ::libs::ievents::runtime::interf::interfaces::ICorrectImage;
using InterfCorrectImageEvent = ::libs::ievents::runtime::interf::InterfCorrectImageEvent;
using IVideoBuf               = ::utils::dbufs::video::IVideoBuf;
using IMCaller                = ::libs::optim::mcalls::IMCaller;
using TransformInfo           = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo          = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
}   // namespace dlls::uplifters::vcorrect::syn
