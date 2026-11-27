#pragma once
/**
\file       vcodec-gen-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
*/

namespace dnodes::codecs::vcodec_gen::syn
{
using InterfCodecImageEvent = ::libs::events_base::runtime::interf::InterfCodecImageEvent;
using ICodecImage           = ::libs::events_base::runtime::interf::interfaces::ICodecImage;
using VideoCodecProp        = ::libs::events_base::props::videos::generic::codec::VideoCodecProp;
using Writes                = ::libs::events_base::props::videos::generic::codec::Writes;
using CodecModes            = ::libs::events_base::props::videos::generic::codec::CodecModes;
using ISystemProperty       = ::libs::iproperties::vers::system::ISystemProperty;
using IVideoBuf             = ::utils::dbufs::video::IVideoBuf;
using HeaderIFrame          = ::dnodes::codecs::codec_gen::HeaderIFrame;
using IncludeSubFolders     = ::libs::utility::files::IncludeSubFolders;
using IncludeFiles          = ::libs::utility::files::IncludeFiles;
using Recursives            = ::libs::utility::files::Recursives;
using TransformInfo         = ::libs::icore::impl::base::obj::dll::TransformInfo;
using CallInterfInfo        = ::libs::icore::impl::base::obj::dll::CallInterfInfo;
using FilterInfo            = ::libs::icore::impl::base::obj::FilterInfo;
using ConnectInfo           = ::libs::icore::impl::base::obj::ConnectInfo;
using ProxyBuf              = ::libs::optim::io::ProxyBuf;
using IEvent                = ::libs::events::IEvent;
using AddEvent2EventsMsg    = ::libs::events_msg::events::AddEvent2EventsMsg;
using IMCaller              = ::libs::optim::mcalls::IMCaller;
using CpuExts               = ::libs::utility::sys::cpu::CpuExts;

namespace minor = ::libs::utility::uids::minor;
}   // namespace dnodes::codecs::vcodec_gen::syn
