#pragma once
/**
\file       all2rgb-dll-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_all2rgb
*/

namespace dlls::convertors::all2rgb
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  auto init () -> void;

  syn::VideoConvertProp::raw_ptr rprops_ = nullptr;   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dlls::convertors::all2rgb
