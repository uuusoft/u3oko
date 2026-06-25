#pragma once
/**
\file       vcodec-gen-syn.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcodec_gen
*/

namespace dlls::codecs::vcodec_gen::syn
{
using InterfCodecImageEvent = ::libs::ievents::runtime::interf::InterfCodecImageEvent;
using ICodecImage           = ::libs::ievents::runtime::interf::interfaces::ICodecImage;
using VideoCodecProp        = ::libs::ievents::props::videos::generic::codec::VideoCodecProp;
using Writes                = ::libs::ievents::props::videos::generic::codec::Writes;
using ISystemProperty       = ::libs::iproperties::vers::system::ISystemProperty;
using IVideoBuf             = ::utils::dbufs::video::IVideoBuf;
using HeaderIFrame          = ::dlls::codecs::codec_gen::HeaderIFrame;
using IncludeSubFolders     = ::libs::helpers::files::IncludeSubFolders;
using IncludeFiles          = ::libs::helpers::files::IncludeFiles;
using Recursives            = ::libs::helpers::files::Recursives;
using TransformInfo         = ::libs::icore::impl::var1::obj::dll::TransformInfo;
using CallInterfInfo        = ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using FilterInfo            = ::libs::icore::impl::var1::obj::FilterInfo;
using ConnectInfo           = ::libs::icore::impl::var1::obj::ConnectInfo;
using ProxyBuf              = ::libs::optim::io::ProxyBuf;
using IEvent                = ::libs::events::IEvent;
using AddEvent2Base         = ::libs::ievents_events::events::AddEvent2Base;
}   // namespace dlls::codecs::vcodec_gen::syn
