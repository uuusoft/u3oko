#pragma once
/**
\file       vgen-diff-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
*/

namespace dlls::gens::vgen_diff
{
class Filter final :
  public ::libs::icore::impl::base::obj::dll::IFilter,
  protected ::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  //  internal typess
  using off2bufs_type = boost::unordered_flat_map< syn::persistent_off_buf_type, ::utils::dbufs::video::IVideoBuf::ptr, ::libs::utility::utils::TransparentStringHash, std::equal_to<> >;
  U3_ADD_SUPER_CLASS (::libs::icore::impl::base::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  auto init_pts (syn::ConnectInfo*) -> void;

  lib::DiffImpl impl_;   //< Реализация вычисления разности
};
}   // namespace dlls::gens::vgen_diff
