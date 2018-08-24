//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       01.08.2017
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_gen_vgen
\brief      ���������� ����������� ��������� ��� ����� ������� ������.
*/

namespace dlls { namespace sources { namespace gen_vgen {
//  syn
using ::libs::icore::impl::var1::obj::helpers::IEmptyInterfObjPath;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::core::path::IInterfPathObj;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::libs::ievents::runtime::mem::BuffsEvent;
using ::libs::ievents::runtime::interf::ICaptureImage;
using ::libs::helpers::sys::cpu::TypeExtCpu;
using ::libs::helpers::fps::FpsController;
using gen_lib::keys2buffs_ptr_type;
using gen_lib::transform_events_type;
using ::libs::helpers::dlls::ForeverLoadDlls;

}}}      // namespace dlls::sources::gen_vgen
