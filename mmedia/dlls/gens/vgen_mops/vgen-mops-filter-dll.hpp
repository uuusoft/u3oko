#pragma once
/**
\file       vgen-mops-filter-dll.hpp
\date       01.10.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vgen_mops
\brief      Объявление фильтра морфологических операций (МО)
*/

namespace dlls::gens::vgen_mops
{
/// Фильтр морфологических операций над изображением
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (syn::CallInterfInfo& info) override;

  void init_pts (syn::ConnectInfo* info);

  lib::MopsImpl impl_;   //< Реализация операций
};
}   // namespace dlls::gens::vgen_mops
