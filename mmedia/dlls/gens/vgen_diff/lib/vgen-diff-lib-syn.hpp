#pragma once
/**
\file       vgen-diff-lib-syn-types.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dlls::gens::vgen_diff::lib::syn
{
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
using IVideoBuf               = ::utils::dbufs::video::IVideoBuf;
using VideoDiffProp           = ::libs::events_base::props::videos::gens::diff::VideoDiffProp;
using TransformInfo           = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo          = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo              = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo             = ::libs::icore::impl::base::obj::ConnectInfo;
using NodeID                  = ::libs::core::graph::NodeID;
using IMCaller                = ::libs::optim::mcalls::IMCaller;
}   // namespace dlls::gens::vgen_diff::lib::syn
