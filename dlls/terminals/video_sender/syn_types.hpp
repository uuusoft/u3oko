//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_video_sender
\brief      ���������� ����������� ��������� ��� ����� ������� ������.
*/

namespace dlls { namespace terminals { namespace video_sender {
//  syn
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::link::ILink;
using ::libs::events::IEvent;
using ::libs::ievents::props::terminals::EndPointProp;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::modules::uuu_gui::appl::io::VideoIO;
using ::libs::ievents::runtime::interf::IBaseId;
using ::libs::ievents::props::base_id::BaseIdProp;
using ::libs::ievents::props::base_id::Buff2ModuleInfo;
using ::libs::ievents::props::base_id::source_name_type;
using ::libs::ievents::props::base_id::id_link_module_type;
using ::utils::dbuffs::video::consts::offs::off_buff_type;

namespace dvideo = ::utils::dbuffs::video;

}}}      // namespace dlls::terminals::video_sender
