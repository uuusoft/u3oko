#pragma once
/**
\file       vgen-conv3_11-filter-dll.hpp
\brief      Base type for all data object
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_vgen_conv
*/

namespace dlls::gens::vgen_conv3_11
{
class Filter final :
  public ::libs::icore::impl::var1::obj::dll::IFilter,
  protected ::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >
{
  public:
  Filter ()          = default;
  virtual ~Filter () = default;

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (syn::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (syn::TransformInfo& info) override;
  virtual void call_int (syn::CallInterfInfo& info) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void itransform ();
  void convolution_buf ();
  void fill_koeffs_for_conv (const syn::BuffVideoConvolutionProp&, ::libs::optim::io::MCallInfo&, ::libs::optim::mcalls::MTFuncInfo&);

  ::libs::optim::io::hioptim                        conv_mod_3x3_;                 //<
  ::libs::optim::io::hioptim                        conv_mod_5x5_;                 //<
  ::libs::optim::io::hioptim                        conv_mod_7x7_;                 //<
  ::libs::optim::io::hioptim                        conv_mod_9x9_;                 //<
  ::libs::optim::io::hioptim                        conv_mod_11x11_;               //<
  syn::base::c3x3::cores::values_core_type          core_3x3_;                     //<
  syn::base::c5x5::cores::values_core_type          core_5x5_;                     //<
  syn::base::c7x7::cores::values_core_type          core_7x7_;                     //<
  syn::base::c9x9::cores::values_core_type          core_9x9_;                     //<
  syn::base::c11x11::cores::values_core_type        core_11x11_;                   //<
  const syn::base::c3x3::cores::values_core_type*   icore_3x3_   = &core_3x3_;     //<
  const syn::base::c5x5::cores::values_core_type*   icore_5x5_   = &core_5x5_;     //<
  const syn::base::c7x7::cores::values_core_type*   icore_7x7_   = &core_7x7_;     //<
  const syn::base::c9x9::cores::values_core_type*   icore_9x9_   = &core_9x9_;     //<
  const syn::base::c11x11::cores::values_core_type* icore_11x11_ = &core_11x11_;   //<
};
}   // namespace dlls::gens::vgen_conv3_11
