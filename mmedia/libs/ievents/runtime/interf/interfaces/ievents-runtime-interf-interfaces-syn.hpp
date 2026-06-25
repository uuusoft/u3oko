#pragma once
/**
\file       ievents-runtime-interf-interfaces-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       17.03.2026
\project    u3_ievents_lib
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

namespace libs::ievents::runtime::interf::interfaces::syn
{
using VideoDriverCaptureProp   = ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp;
using VideoDriverProp          = ::libs::ievents::props::videos::generic::driver::VideoDriverProp;
using SystemSpecificDriverProp = ::libs::ievents::runtime::video::SystemSpecificDriverProp;
using VideoCodecProp           = ::libs::ievents::props::videos::generic::codec::VideoCodecProp;
using VideoCorrectProp         = ::libs::ievents::props::videos::generic::correct::VideoCorrectProp;
using IVideoBuf                = ::utils::dbufs::video::IVideoBuf;
using TransformInfo            = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using NodeID                   = ::libs::core::graph::NodeID;
using off_buf_type             = ::utils::dbufs::video::consts::offs::off_buf_type;
using source_name_type         = ::libs::ievents::props::base_id::source_name_type;
}   // namespace libs::ievents::runtime::interf::interfaces::syn
