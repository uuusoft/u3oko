#pragma once
/**
\file       vcorrect-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect::syn
{
using VideoCorrectProp        = ::libs::events_base::props::videos::generic::correct::VideoCorrectProp;
using ICorrectImage           = ::libs::events_base::runtime::interf::interfaces::ICorrectImage;
using InterfCorrectImageEvent = ::libs::events_base::runtime::interf::InterfCorrectImageEvent;
using IVideoBuf               = ::utils::dbufs::video::IVideoBuf;
using IMCaller                = ::libs::optim::mcalls::IMCaller;
using TransformInfo           = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo          = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo              = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo             = ::libs::icore::impl::var1::obj::ConnectInfo;
using ProxyBuf                = ::libs::optim::io::ProxyBuf;
using IEvent                  = ::libs::events::IEvent;
using AddEvent2EventsMsg      = ::libs::events_msg::events::AddEvent2EventsMsg;
}   // namespace dlls::uplifters::vcorrect::syn
