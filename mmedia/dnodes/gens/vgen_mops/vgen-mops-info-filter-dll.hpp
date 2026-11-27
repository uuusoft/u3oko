#pragma once
/**
\file       vgen-mops-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2017
\brief      Включаемый файл для морфологических операций
*/

namespace dnodes::gens::vgen_mops
{
/// Загружаемые данные для фильтра морфологических операций над изображением
struct InfoFilter final : public ::libs::icore::impl::base::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  auto init () -> void;

  syn::VideoMorphologyProp::raw_ptr rprops_ = nullptr;   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dnodes::gens::vgen_mops
