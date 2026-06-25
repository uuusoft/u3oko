#pragma once
/**
\file       all2hsl-dll-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_all2hsl
*/

namespace dlls::convertors::all2hsl
{
/// Свойства данного фильтра по преобразованию форматов в HSL
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  public:
  InfoFilter ();
  virtual ~InfoFilter () = default;

  InfoFilter (const InfoFilter&)                = delete;
  InfoFilter& operator= (const InfoFilter&)     = delete;
  InfoFilter (InfoFilter&&) noexcept            = delete;
  InfoFilter& operator= (InfoFilter&&) noexcept = delete;

  auto init () -> void;

  syn::VideoConvertProp::raw_ptr rprops_      = nullptr;   //< Настроенный указатель на свойства (для удобства)
  bool                           strip_color_ = false;     //< Флаг-требование, отбрасывать цвет при преобразовании, расширряет условие из свойств, т.к ряд форматов по определению не несут цвета
};
}   // namespace dlls::convertors::all2hsl
