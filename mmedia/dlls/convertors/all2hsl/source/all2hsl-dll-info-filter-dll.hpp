#pragma once
/**
\file       all2hsl-dll-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
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

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  void init ();

  syn::VideoConvertProp::raw_ptr rprops_;        //< Настроенный указатель на свойства (для удобства)
  bool                           strip_color_;   //< Флаг-требование, отбрасывать цвет при преобразовании, расширряет условие из свойств, т.к ряд форматов по определению не несут цвета
};
}   // namespace dlls::convertors::all2hsl
