#pragma once
/**
\file       all2rgb-dll-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
*/

namespace dnodes::convertors::all2rgb
{
struct InfoFilter final : public ::libs::icore::impl::base::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  auto init () -> void;

  syn::VideoConvertProp::raw_ptr rprops_ = nullptr;   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dnodes::convertors::all2rgb
