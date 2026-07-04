#pragma once
/**
\file       events-runtime-interf-interfaces-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.03.2026
\project    u3_events_base_lib
*/
// EAI-REFACT forward
namespace libs::icore::impl::var1::obj::dll
{
struct TransformInfo;
}

namespace libs::core::graph
{
class NodeID;
}

namespace libs::events_base::runtime::interf::interfaces::syn
{
using VideoDriverCaptureProp   = ::libs::events_base::props::videos::generic::driver::VideoDriverCaptureProp;
using VideoDriverProp          = ::libs::events_base::props::videos::generic::driver::VideoDriverProp;
using SystemSpecificDriverProp = ::libs::events_base::runtime::video::SystemSpecificDriverProp;
using VideoCodecProp           = ::libs::events_base::props::videos::generic::codec::VideoCodecProp;
using VideoCorrectProp         = ::libs::events_base::props::videos::generic::correct::VideoCorrectProp;
using IVideoBuf                = ::utils::dbufs::video::IVideoBuf;
using TransformInfo            = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using NodeID                   = ::libs::core::graph::NodeID;
using off_buf_type             = ::utils::dbufs::video::consts::offs::off_buf_type;
using source_name_type         = ::libs::events_base::props::base_id::source_name_type;
}   // namespace libs::events_base::runtime::interf::interfaces::syn
