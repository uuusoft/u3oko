#pragma once
/**
\file       vgen-diff-filter-dll.hpp
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vgen_diff
*/

namespace dlls::gens::vgen_diff
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  private:
  //  internal typess
  using off2bufs_type = std::unordered_map< ::utils::dbufs::video::consts::offs::off_buf_type, ::utils::dbufs::video::IVideoBuf::ptr >;
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);

  lib::DiffImpl impl_;   //< Реализация вычисления разности
};
}   // namespace dlls::gens::vgen_diff
