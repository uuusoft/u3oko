#pragma once
/**
\file       syn.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       13.09.2018
\copyright  www.uuusoft.com
\project    uuu_vgd_motion
\brief      empty brief
*/

namespace dlls { namespace gens { namespace vgen_motion {
//  syn
using ::libs::ievents::props::videos::generics::motion_est::VideoEstMotionProp;
using ::libs::ievents::props::videos::generics::motion_est::EventBuffsInfo;
using ::utils::dbuffs::video::consts::offs::off_buff_type;
using ::utils::dbuffs::video::IVideoBuff;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;

}}}      // namespace dlls::gens::vgen_motion
