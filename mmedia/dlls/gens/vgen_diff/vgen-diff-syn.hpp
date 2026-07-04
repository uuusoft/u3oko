#pragma once
/**
\file       vgen-diff-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgen_diff
*/

namespace dlls::gens::vgen_diff::syn
{
using buf2info_type      = std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, ::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp >;
using TransformInfo      = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo     = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo         = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo        = ::libs::icore::impl::var1::obj::ConnectInfo;
using ProxyBuf           = ::libs::optim::io::ProxyBuf;
using IEvent             = ::libs::events::IEvent;
using AddEvent2EventsMsg = ::libs::events_msg::events::AddEvent2EventsMsg;
using VideoDiffProp      = ::libs::events_base::props::videos::gens::diff::VideoDiffProp;
}   // namespace dlls::gens::vgen_diff::syn
