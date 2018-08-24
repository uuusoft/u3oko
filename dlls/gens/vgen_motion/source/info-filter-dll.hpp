#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgd_motion
\brief      empty brief
*/

namespace dlls { namespace gens { namespace vgen_motion {
//  syn
typedef ::libs::ievents::props::videos::generics::motion_est::VideoEstMotionProp VideoEstMotionProp;
typedef ::libs::ievents::props::videos::generics::motion_est::BuffEventInfo      BuffEventInfo;
typedef ::utils::dbuffs::video::consts::offs::off_buff_type                      off_buff_type;
typedef ::utils::dbuffs::video::IVideoBuff                                       IVideoBuff;
typedef ::libs::icore::impl::var1::obj::PointFilter                              PointFilter;
typedef ::libs::icore::impl::var1::obj::FilterInfo                               FilterInfo;
typedef ::libs::icore::impl::var1::obj::dll::TransformInfo                       TransformInfo;
typedef ::libs::icore::impl::var1::obj::dll::CallInterfInfo                      CallInterfInfo;
typedef ::libs::icore::impl::var1::obj::ConnectInfo                              ConnectInfo;
/**
  \brief  Empty description
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  typedef VideoEstMotionProp props_type;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  void init ();

  ::libs::events::IEvent::ptr props_;       //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;      //< Настроенный указатель на свойства (для удобства).
};

}}}      // namespace dlls::gens::vgen_motion
