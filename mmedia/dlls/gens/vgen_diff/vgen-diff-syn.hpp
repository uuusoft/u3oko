#pragma once
/**
\file       vgen-diff-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dlls::gens::vgen_diff::syn
{
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
using InfoBuffVideoDiffProp   = ::libs::events_base::props::videos::gens::diff::InfoBuffVideoDiffProp;
using buf2info_type           = std::pair< persistent_off_buf_type, syn::InfoBuffVideoDiffProp >;
using TransformInfo           = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo          = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo              = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo             = ::libs::icore::impl::base::obj::ConnectInfo;
using ProxyBuf                = ::libs::optim::io::ProxyBuf;
using IEvent                  = ::libs::events::IEvent;
using AddEvent2EventsMsg      = ::libs::events_msg::events::AddEvent2EventsMsg;
using VideoDiffProp           = ::libs::events_base::props::videos::gens::diff::VideoDiffProp;
}   // namespace dlls::gens::vgen_diff::syn
