#pragma once
/**
\file       info-filter-dll.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_dlls_vec2image
\brief      empty brief
*/

namespace dlls { namespace utils { namespace vec2image1 {
//syn
using ::libs::ievents::props::videos::generics::vec2image::Vec2ImageProp;
using ::libs::icore::impl::var1::obj::PointFilter;
using ::libs::icore::impl::var1::obj::FilterInfo;
using ::libs::icore::impl::var1::obj::dll::TransformInfo;
using ::libs::icore::impl::var1::obj::dll::CallInterfInfo;
using ::libs::icore::impl::var1::obj::ConnectInfo;
using ::utils::dbuffs::video::IVideoBuff;
using BuffEventInfo = ::libs::ievents::props::videos::generics::vec2image::BuffEventInfoVec2Image1;
/**
  \brief  Empty description
  */
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter
{
  // ext types
  using props_type = Vec2ImageProp;

  InfoFilter ();

  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& _src) = delete;
  InfoFilter& operator= (const InfoFilter& _src) = delete;

  void init ();

  ::libs::events::IEvent::ptr props_;       //< Загружаемые из xml файла свойства фильтра.
  props_type::raw_ptr         rprops_;      //< Настроенный указатель на свойства (для удобства).
};

}}}      // namespace dlls::utils::vec2image1
