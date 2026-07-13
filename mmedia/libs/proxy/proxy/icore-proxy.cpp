/**
\file       icore-proxy.cpp
\date       15.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/events/includes.hpp"
#include "mmedia/libs/link/_make/libs-link-includes.hpp"
#include "mmedia/libs/core/libs-cores-core-includes.hpp"
#include "mmedia/libs/icore/libs-icore-includes.hpp"
#include "icore-proxy.hpp"

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vcodec_gen () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vcd_all2hsl () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vcd_all2rgb () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

#if (U3_LIBS_ENABLE_DETECT_FACE_VDD == 1)
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_detect_face () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
#endif

#if (U3_LIBS_ENABLE_VDETECT1_VDD == 1)
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_detect_move () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
#endif

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vfn_freq_domain () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vfn_space () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vfn_time () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_base_id () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vgd_vgen_conv3_11 () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vgd_vgen_diff () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vgd_vgen_mops () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vsa_fixed () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vsa_flow () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vsd_gen_vgen () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vcorrect () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vgradient () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vhistogram () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vmatrix () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vsharper () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdd_vtexter () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vut_vec2image () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vts_video_sender () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vdm_mix_multiplier () -> ::libs::icore::impl::var1::obj::dll::IFilter*;
extern "C" BOOST_SYMBOL_EXPORT auto create_impl_vgd_vgen_motion () -> ::libs::icore::impl::var1::obj::dll::IFilter*;

namespace libs::proxy
{
auto
get_create_data_path_module_func (const std::string& plib_id) -> std::function< libs::icore::impl::var1::obj::dll::create_impl_func_type >
{
  const auto lib_id = libs::utility::dlls::undecorate_dll_name (plib_id);

  if (lib_id == "vts_video_sender")
  {
    return create_impl_vts_video_sender;
  }
#if (U3_LIBS_ENABLE_MIX_MULTIPLIER_VDM == 1)
  if (lib_id == "vdm_mix_multiplier")
  {
    return create_impl_vdm_mix_multiplier;
  }
#endif
  if (lib_id == "vdd_vcodec_gen")
  {
    return create_impl_vdd_vcodec_gen;
  }

  if (lib_id == "vcd_all2hsl")
  {
    return create_impl_vcd_all2hsl;
  }

  if (lib_id == "vcd_all2rgb")
  {
    return create_impl_vcd_all2rgb;
  }
#if (U3_LIBS_ENABLE_DETECT_FACE_VDD == 1)
  if (lib_id == "vdd_detect_face")
  {
    return create_impl_vdd_detect_face;
  }
#endif
#if (U3_LIBS_ENABLE_VDETECT1_VDD == 1)
  if (lib_id == "vdd_detect_move")
  {
    return create_impl_vdd_detect_move;
  }
#endif
#if (U3_LIBS_ENABLE_VCLEANER_FREQ_VDD == 1)
  if (lib_id == "vfn_freq_domain")
  {
    return create_impl_vfn_freq_domain;
  }
#endif
  if (lib_id == "vfn_space")
  {
    return create_impl_vfn_space;
  }

  if (lib_id == "vfn_time")
  {
    return create_impl_vfn_time;
  }

  if (lib_id == "vdd_base_id")
  {
    return create_impl_vdd_base_id;
  }

  if (lib_id == "vgd_vgen_conv3_11")
  {
    return create_impl_vgd_vgen_conv3_11;
  }

  if (lib_id == "vgd_vgen_diff")
  {
    return create_impl_vgd_vgen_diff;
  }

  if (lib_id == "vgd_vgen_mops")
  {
    return create_impl_vgd_vgen_mops;
  }
#if (U3_LIBS_ENABLE_FIXED_VSA == 1)
  if (lib_id == "vsa_fixed")
  {
    return create_impl_vsa_fixed;
  }
#endif
#if (U3_LIBS_ENABLE_FLOW_VSA == 1)
  if (lib_id == "vsa_flow")
  {
    return create_impl_vsa_flow;
  }
#endif
  if (lib_id == "vsd_gen_vgen")
  {
    return create_impl_vsd_gen_vgen;
  }

  if (lib_id == "vdd_vcorrect")
  {
    return create_impl_vdd_vcorrect;
  }
#if (U3_LIBS_ENABLE_VGRADIENT_VDD == 1)
  if (lib_id == "vdd_vgradient")
  {
    return create_impl_vdd_vgradient;
  }
#endif
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
  if (lib_id == "vdd_vhistogram")
  {
    return create_impl_vdd_vhistogram;
  }

  if (lib_id == "vdd_vmatrix")
  {
    return create_impl_vdd_vmatrix;
  }

  if (lib_id == "vdd_vsharper")
  {
    return create_impl_vdd_vsharper;
  }

  if (lib_id == "vdd_vtexter")
  {
    return create_impl_vdd_vtexter;
  }
#endif
#if (U3_LIBS_ENABLE_VEC2IMAGE_VUT == 1)
  if (lib_id == "vut_vec2image")
  {
    return create_impl_vut_vec2image;
  }
#endif
  if (lib_id == "vgd_vgen_motion")
  {
    return create_impl_vgd_vgen_motion;
  }

  U3_THROW_EXCEPT ("find create module funct" + TOLOG (lib_id) + TOLOG (plib_id));
}
}   // namespace libs::proxy
