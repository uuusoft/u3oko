#pragma once
/**
\file       vgen-mops-lib-syn.hpp
\date       16.07.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vgen_mops_lib
*/

namespace dlls::gens::vgen_mops::lib::syn
{
using MorphBuffInfo        = ::libs::ievents::props::videos::generic::morph::MorphBuffInfo;
using VideoMorphologyProp  = ::libs::ievents::props::videos::generic::morph::VideoMorphologyProp;
using MorphOperationParams = ::libs::ievents::props::videos::generic::morph::MorphOperationParams;
using TransformInfo        = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo       = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo           = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo          = ::libs::icore::impl::var1::obj::ConnectInfo;
using NodeID               = ::libs::core::graph::NodeID;
using IMCaller             = ::libs::optim::mcalls::IMCaller;
using off_buf2info_type    = std::pair< ::utils::dbufs::video::consts::offs::off_buf_type, MorphBuffInfo >;
}   // namespace dlls::gens::vgen_mops::lib::syn
