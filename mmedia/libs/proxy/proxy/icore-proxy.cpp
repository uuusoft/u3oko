/**
\file       icore-proxy.cpp
\date       15.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/events/includes.hpp"
#include "mmedia/libs/link/libs-link-includes.hpp"
#include "mmedia/libs/core/libs-cores-core-includes.hpp"
#include "mmedia/libs/icore/libs-icore-includes.hpp"
#include "icore-proxy.hpp"

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vcodec_gen ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vcd_all2hsl ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vcd_all2rgb ();

#if defined(U3_LIBS_ENABLE_DETECT_FACE_VDD)
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_detect_face ();
#endif
#if defined(U3_LIBS_ENABLE_VDETECT1_VDD)
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_detect_move ();
#endif

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vfn_freq_domain ();

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vfn_space ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vfn_time ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_base_id ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vgd_vgen_conv3_11 ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vgd_vgen_diff ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vgd_vgen_mops ();

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vsa_fixed ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vsa_flow ();

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vsd_gen_vgen ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vcorrect ();

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vgradient ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vhistogram ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vmatrix ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vsharper ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdd_vtexter ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vut_vec2image ();

extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vts_video_sender ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vdm_mix_multiplier ();
extern "C" BOOST_SYMBOL_EXPORT ::libs::icore::impl::var1::obj::dll::IFilter* create_impl_vgd_vgen_motion ();

namespace libs::proxy
{
::boost::function< libs::icore::impl::var1::obj::dll::create_impl_func_type >
get_create_data_path_module_funct (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);

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

#if defined(U3_LIBS_ENABLE_DETECT_FACE_VDD)
  if (lib_id == "vdd_detect_face")
  {
    return create_impl_vdd_detect_face;
  }
#endif

#if defined(U3_LIBS_ENABLE_VDETECT1_VDD)
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
#if 0
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

  U3_THROW_EXCEPTION ("find create module funct" + TOLOG (lib_id) + TOLOG (plib_id));
}
}   // namespace libs::proxy
