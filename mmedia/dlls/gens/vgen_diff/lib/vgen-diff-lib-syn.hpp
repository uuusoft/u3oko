#pragma once
/**
\file       vgen-diff-lib-syn-types.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgen_diff_lib
*/

namespace dlls::gens::vgen_diff::lib::syn
{
using IVideoBuf      = ::utils::dbufs::video::IVideoBuf;
using VideoDiffProp  = ::libs::events_base::props::videos::gens::diff::VideoDiffProp;
using TransformInfo  = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo     = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo    = ::libs::icore::impl::var1::obj::ConnectInfo;
using NodeID         = ::libs::core::graph::NodeID;
using IMCaller       = ::libs::optim::mcalls::IMCaller;
}   // namespace dlls::gens::vgen_diff::lib::syn
