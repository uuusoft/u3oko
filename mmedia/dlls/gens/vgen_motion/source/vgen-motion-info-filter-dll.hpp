#pragma once
/**
\file       vgen-motion-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dlls::gens::vgen_motion
{
struct InfoFilter final : public ::libs::icore::impl::base::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  auto init () -> void;

  syn::VideoEstMotionProp::raw_ptr rprops_ { nullptr };   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dlls::gens::vgen_motion
