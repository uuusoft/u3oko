#pragma once
/**
\file       vgen-diff-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vgen_diff
*/

namespace dlls::gens::vgen_diff
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  InfoFilter (const InfoFilter& src)            = delete;
  InfoFilter& operator= (const InfoFilter& src) = delete;

  auto init () -> void;

  ::libs::ievents::props::videos::gens::diff::VideoDiffProp::raw_ptr rprops_ = nullptr;   //< Настроенный указатель на свойства (для удобства)
};
}   // namespace dlls::gens::vgen_diff
