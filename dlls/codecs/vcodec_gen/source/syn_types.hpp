//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcodec_gen
\brief      ���������� ����������� ��������� ��� ����� ������� ������.
*/

namespace dlls { namespace codecs { namespace vcodec_gen {
//  syn
using ::utils::dbuffs::video::IVideoBuff;
using ::utils::mem_functs::IBlockMem;
using ::libs::helpers::utils::cuuid;
using ::libs::helpers::dlls::ForeverLoadDlls;
using ::libs::optim::io::MCallInfo;
using ::libs::helpers::fps::FpsController;
using ::libs::optim::io::ProxyBuff;
using ::libs::optim::mcalls::InfoMFunct;
using ::libs::optim::mcalls::CallerImpl;
using ::libs::ievents::props::videos::generics::codec::VideoCodecProp;
using ::libs::ievents::props::videos::generics::codec::OverrideCodecDataType;
using ::libs::ievents::runtime::interf::ICodecImage;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::dlls::codecs::codec_gen::HeaderIFrameHSL;
using ::dlls::codecs::codec_gen::HeaderIFrame;

}}}      // namespace dlls::codecs::vcodec_gen
