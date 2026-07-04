#pragma once
/**
\file       base_id-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
\project    u3_base_id_dll
*/

namespace dlls::base_id
{
struct InfoFilter final : public ::libs::icore::impl::var1::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  syn::BaseIdProp::raw_ptr rprops_ = nullptr;   //<
};
}   // namespace dlls::base_id
