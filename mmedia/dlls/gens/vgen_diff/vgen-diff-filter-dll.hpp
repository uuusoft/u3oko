#pragma once
/**
\file       vgen-diff-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_vgen_diff
*/

namespace dlls::gens::vgen_diff
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  //  internal typess
  using off2bufs_type = boost::unordered_flat_map< ::utils::dbufs::video::consts::offs::off_buf_type, ::utils::dbufs::video::IVideoBuf::ptr >;
  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo& info) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;

  auto init_pts (syn::ConnectInfo*) -> void;

  lib::DiffImpl impl_;   //< Реализация вычисления разности
};
}   // namespace dlls::gens::vgen_diff
