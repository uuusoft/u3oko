//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn_types.hpp
\date       16.07.2018
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_vgen_mops_lib
\brief      Объявление сокращенных синонимов для всего данного модуля.
*/

namespace dlls { namespace gens { namespace vgen_mops { namespace lib {
//  синонимы к типам.
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::buffs::Buffs;
using ::libs::events::IEvent;
using ::libs::ievents::props::videos::generic::morph::VideoMorphologyProp;
using ::libs::optim::mcalls::CallerImpl;
using ::libs::ievents::props::videos::generic::morph::BuffInfo;
using ::libs::ievents::props::videos::generic::morph::ParamsOperation;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::ievents::props::videos::generic::morph::TypeOperation;
using ::libs::optim::mcalls::InfoMFunct;
using ::libs::optim::io::MCallInfo;
using OffBuff2Info = std::pair<off_buff_type, ::libs::ievents::props::videos::generic::morph::BuffInfo>;

}}}}      // namespace dlls::gens::vgen_mops::lib
