//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vcodec_mjpg
\brief      ���������� ����������� ��������� ��� ����� ������� ������.
*/

namespace dlls { namespace codecs { namespace vcodec_mjpg {
//  syn
using ::libs::optim::io::MCallInfo;
using ::libs::optim::io::ProxyBuff;
using ::libs::optim::mcalls::InfoMFunct;
using ::libs::optim::mcalls::CallerImpl;
using ::libs::ievents::props::videos::generics::codec::VideoCodecProp;
using ::utils::dbuffs::video::IVideoBuff;
using ::utils::mem_functs::IBlockMem;
using ::dlls::codecs::codec_gen::HeaderIFrame;
using ::libs::buffs::Buffs;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using codec_gen::StatisticInfo;
using events_type = ::libs::icore::impl::var1::obj::dll::TransformInfo::events_type;

}}}      // namespace dlls::codecs::vcodec_mjpg
