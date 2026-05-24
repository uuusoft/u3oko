#pragma once
/**
\file       vgen-motion-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgd_motion
*/

namespace dlls::gens::vgen_motion
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  // ext types
  using props_type = ::libs::ievents::props::videos::generic::motion_est::VideoEstMotionProp;

  InfoFilter ();
  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  void init ();

  props_type::raw_ptr rprops_;   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dlls::gens::vgen_motion
