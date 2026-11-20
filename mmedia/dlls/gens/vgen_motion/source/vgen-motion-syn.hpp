#pragma once
/**
\file       vgen-motion-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       13.09.2018
*/

namespace dlls::gens::vgen_motion::syn
{
using VideoEstMotionProp      = ::libs::events_base::props::videos::generic::motion_est::VideoEstMotionProp;
using EventBufsMotionEst      = ::libs::events_base::props::videos::generic::motion_est::EventBufsMotionEst;
using IVideoBuf               = ::utils::dbufs::video::IVideoBuf;
using TransformInfo           = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo          = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo              = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo             = ::libs::icore::impl::base::obj::ConnectInfo;
using ProxyBuf                = ::libs::optim::io::ProxyBuf;
using IEvent                  = ::libs::events::IEvent;
using AddEvent2EventsMsg      = ::libs::events_msg::events::AddEvent2EventsMsg;
using mem_var_type            = ::utils::dbufs::IBuf::mem_var_type;
using Dims                    = ::utils::dbufs::video::Dims;
using MemVars                 = ::utils::dbufs::MemVars;
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
}   // namespace dlls::gens::vgen_motion::syn
