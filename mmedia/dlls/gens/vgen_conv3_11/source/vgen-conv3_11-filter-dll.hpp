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
  Filter ();
  virtual ~Filter ();

  private:
  // internal types
  U3_HELPER_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl< InfoFilter >)
  // IFilter overrides
  virtual void load_int (::libs::icore::impl::var1::obj::FilterInfo* info, const ::pugi::xml_named_node_iterator& node) override;
  virtual void transform_int (::libs::icore::impl::var1::obj::dll::TransformInfo& info) override;
  virtual void call_int (::libs::icore::impl::var1::obj::dll::CallInterfInfo& info) override;

  void init_pts (::libs::icore::impl::var1::obj::ConnectInfo* info);
  void itransform ();
  void convolution_buf ();

  void fill_koeffs_for_conv (
    const syn::BuffVideoConvolutionProp& ibuf,
    ::libs::optim::io::MCallInfo&        cinfo,
    ::libs::optim::mcalls::InfoMFunct&   tfunct);

  ::libs::optim::io::hioptim                                              conv_mod_3x3_;     //<
  ::libs::optim::io::hioptim                                              conv_mod_5x5_;     //<
  ::libs::optim::io::hioptim                                              conv_mod_7x7_;     //<
  ::libs::optim::io::hioptim                                              conv_mod_9x9_;     //<
  ::libs::optim::io::hioptim                                              conv_mod_11x11_;   //<
  ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type        core_3x3_;         //<
  ::libs::optim::s16bit::conv::base::c5x5::cores::TCore                   core_5x5_;         //<
  ::libs::optim::s16bit::conv::base::c7x7::cores::TCore                   core_7x7_;         //<
  ::libs::optim::s16bit::conv::base::c9x9::cores::TCore                   core_9x9_;         //<
  ::libs::optim::s16bit::conv::base::c11x11::cores::TCore                 core_11x11_;       //<
  const ::libs::optim::s16bit::conv::base::c3x3::cores::values_core_type* icore_3x3_;        //<
  const ::libs::optim::s16bit::conv::base::c5x5::cores::TCore*            icore_5x5_;        //<
  const ::libs::optim::s16bit::conv::base::c7x7::cores::TCore*            icore_7x7_;        //<
  const ::libs::optim::s16bit::conv::base::c9x9::cores::TCore*            icore_9x9_;        //<
  const ::libs::optim::s16bit::conv::base::c11x11::cores::TCore*          icore_11x11_;      //<
};
}   // namespace dlls::gens::vgen_conv3_11
