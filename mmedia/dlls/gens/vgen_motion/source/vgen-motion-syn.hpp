#pragma once
/**
\file       vgen-motion-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       13.09.2018
\project    u3_vgd_motion
*/

namespace dlls::gens::vgen_motion::syn
{
using EventBufsInfoMotionEst = ::libs::ievents::props::videos::generic::motion_est::EventBufsInfoMotionEst;
using IVideoBuf              = ::utils::dbufs::video::IVideoBuf;
using TransformInfo          = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo         = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo             = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo            = ::libs::icore::impl::var1::obj::ConnectInfo;
using ProxyBuf               = ::libs::optim::io::ProxyBuf;
using IEvent                 = ::libs::events::IEvent;
using AddEvent2Base          = ::libs::ievents_events::events::AddEvent2Base;
}   // namespace dlls::gens::vgen_motion::syn
