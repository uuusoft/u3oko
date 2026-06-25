#pragma once
/**
\file       v4l2-vgen-syn.hpp
\author     Erashov Anton erashov2026@proton.me
\date       20.02.2026
\project    u3_v4l2_vgen
*/

namespace dlls::sources::v4l2_vgen::syn
{
using time_point_type            = std::chrono::time_point< std::chrono::high_resolution_clock >;
using IHardwareCorrect           = ::dlls::sources::gen_lib::interfs::IHardwareCorrect;
using IHardwareCapture           = ::dlls::sources::gen_lib::interfs::IHardwareCapture;
using InterfCorrectImageEvent    = ::libs::ievents::runtime::interf::InterfCorrectImageEvent;
using InterfCaptureImageEvent    = ::libs::ievents::runtime::interf::InterfCaptureImageEvent;
using VideoDriverProp            = ::libs::ievents::props::videos::generic::driver::VideoDriverProp;
using VideoDriverCaptureProp     = ::libs::ievents::props::videos::generic::driver::VideoDriverCaptureProp;
using VideoDriverCapturePropInfo = ::libs::ievents::props::videos::generic::driver::VideoDriverCapturePropInfo;
using LinksVideoDriverProp       = ::libs::ievents::props::videos::generic::driver::LinksVideoDriverProp;
using IVideoBuf                  = ::utils::dbufs::video::IVideoBuf;
using VideoCorrectProp           = ::libs::ievents::props::videos::generic::correct::VideoCorrectProp;
using IEvent                     = ::libs::events::IEvent;
using DataSourceInfo             = ::libs::imdata_events::events::DataSourceInfo;
using pkeys2bufs_type            = ::dlls::sources::gen_lib::syn::pkeys2bufs_type;
using tevents_type               = ::dlls::sources::gen_lib::syn::tevents_type;
}   // namespace dlls::sources::v4l2_vgen::syn
