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
/// Модуль для коррекции базовых свойств изображения (насыщенность/тон/яркость.etc)
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ();
  virtual ~Filter () = default;

  private:
  // internal types
  U3_ADD_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)

  // IFilter overrides
  virtual auto load_int (syn::FilterInfo*, const ::pugi::xml_named_node_iterator&) -> void override;
  virtual auto transform_int (syn::TransformInfo&) -> void override;
  virtual auto call_int (syn::CallInterfInfo&) -> void override;
  virtual auto stop_int () -> void override;

  auto init_pts (syn::ConnectInfo*) -> void;
  auto itransform () -> void;
};
}   // namespace dlls::uplifters::vcorrect
