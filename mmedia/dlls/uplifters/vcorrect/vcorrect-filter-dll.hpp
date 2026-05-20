#pragma once
/**
\file       vcorrect-filter-dll.hpp
\brief      Filter for corrected image
\date       01.01.2016
\author     Erashov Anton erashov2026@proton.me
\project    u3_vcorrect_vdd
*/

namespace dlls::uplifters::vcorrect
{
/// Модуль для коррекции базовых свойств изображения (насыщенность/тон/яркость.etc).
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
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (syn::CallInterfInfo& info) override;
  virtual void stop_int () override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void itransform ();
};
}   // namespace dlls::uplifters::vcorrect
