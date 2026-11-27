#pragma once
/**
\file       vgen-mops-lib-syn.hpp
\date       16.07.2018
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::gens::vgen_mops::lib::syn
{
using ISystemProperty         = ::libs::iproperties::vers::system::ISystemProperty;
using MorphBuffInfo           = ::libs::events_base::props::videos::generic::morph::MorphBuffInfo;
using VideoMorphologyProp     = ::libs::events_base::props::videos::generic::morph::VideoMorphologyProp;
using MorphOperationParams    = ::libs::events_base::props::videos::generic::morph::MorphOperationParams;
using TransformInfo           = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo          = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo              = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo             = ::libs::icore::impl::base::obj::ConnectInfo;
using NodeID                  = ::libs::core::graph::NodeID;
using IMCaller                = ::libs::optim::mcalls::IMCaller;
using persistent_off_buf_type = ::utils::dbufs::video::consts::offs::persistent_off_buf_type;
using off_buf2info_type       = std::pair< persistent_off_buf_type, MorphBuffInfo >;
using MorphOps                = ::libs::events_base::props::videos::generic::morph::MorphOps;

namespace c3x3   = ::libs::optim::s16bit::conv::base::c3x3;
namespace c5x5   = ::libs::optim::s16bit::conv::base::c5x5;
namespace c7x7   = ::libs::optim::s16bit::conv::base::c7x7;
namespace c9x9   = ::libs::optim::s16bit::conv::base::c9x9;
namespace c11x11 = ::libs::optim::s16bit::conv::base::c11x11;
}   // namespace dnodes::gens::vgen_mops::lib::syn
