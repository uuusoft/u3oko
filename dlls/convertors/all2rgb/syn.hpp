//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       syn.hpp
\date       01.05.2017
\author     Erashov A. /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\copyright  www.uuusoft.com
\project    uuu_all2rgb
\brief      Внутренний интерфейс включения данного модуля.
*/

namespace dlls { namespace convertors { namespace all2rgb {
//  syn
using ::libs::ievents::props::videos::generics::convert::VideoConvertProp;
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::libs::optim::mcalls::InfoMFunct;
using ::libs::optim::MCallInfo;
using ::libs::helpers::utils::cuuid;

namespace svideo = utils::dbuffs::video;

}}}      // namespace dlls::convertors::all2rgb
