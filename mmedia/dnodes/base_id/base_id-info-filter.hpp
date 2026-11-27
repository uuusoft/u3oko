#pragma once
/**
\file       base_id-info-filter-dll.hpp
\author     Erashov Anton erashov2026@proton.me
\date       16.07.2018
*/

namespace dnodes::base_id
{
struct InfoFilter final : public ::libs::icore::impl::base::obj::dll::BaseInfoFilter {
  InfoFilter ();
  virtual ~InfoFilter () = default;

  syn::BaseIdProp::raw_ptr rprops_ = nullptr;   //<
};
}   // namespace dnodes::base_id
