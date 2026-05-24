#pragma once
/**
\file       vgen-mops-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2017
\project    u3_vgen_mops
\brief      Включаемый файл для морфологических операций
*/

namespace dlls::gens::vgen_mops
{
/// Загружаемые данные для фильтра морфологических операций над изображением
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter ();

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  void init ();

  syn::VideoMorphologyProp::raw_ptr rprops_;   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dlls::gens::vgen_mops
