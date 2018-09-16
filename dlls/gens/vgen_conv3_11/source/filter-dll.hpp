#pragma once
/**
\file       filter-dll.hpp
\brief      Base type for all data object
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_vgen_conv
\brief    
*/

namespace dlls { namespace gens { namespace vgen_conv3_11 {
/**
\brief  empty brief
*/
class Filter final : public ::libs::icore::impl::var1::obj::dll::IFilter,
                     protected ::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>
{
  public:
  Filter ();

  virtual ~Filter ();


  private:
  // int types
  UUU_THIS_TYPE_HAS_SUPER_CLASS (::libs::icore::impl::var1::obj::dll::FilterImpl<InfoFilter>);
  // IFilter overrides
  virtual void load_int (FilterInfo* info, const base_functs::xml::itn& _node) override;
  virtual void transform_int (TransformInfo& _info) override;
  virtual void call_int (CallInterfInfo& _info) override;

  void init_pts (ConnectInfo* info);

  void itransform ();

  void convolution_buff ();

  void fill_koeffs_for_conv (const BuffVideoConvolutionProp& _ibuff, ::libs::optim::io::MCallInfo& _cinfo, ::libs::optim::mcalls::InfoMFunct& _tfunct);

  hioptim           conv_mod_3x3_;        //< ???
  hioptim           conv_mod_5x5_;        //< ???
  hioptim           conv_mod_7x7_;        //< ???
  hioptim           conv_mod_9x9_;        //< ???
  hioptim           conv_mod_11x11_;      //< ???
  TCore3x3          core_3x3_;            //< ???
  TCore5x5          core_5x5_;            //< ???
  TCore7x7          core_7x7_;            //< ???
  TCore9x9          core_9x9_;            //< ???
  TCore11x11        core_11x11_;          //< ???
  const TCore3x3*   icore_3x3_;           //< ???
  const TCore5x5*   icore_5x5_;           //< ???
  const TCore7x7*   icore_7x7_;           //< ???
  const TCore9x9*   icore_9x9_;           //< ???
  const TCore11x11* icore_11x11_;         //< ???
};

}}}      // namespace dlls::gens::vgen_conv3_11
