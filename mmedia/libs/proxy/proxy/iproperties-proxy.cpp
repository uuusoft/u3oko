/**
\file       iproperties-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "iproperties-proxy.hpp"

namespace libs::proxy
{
std::vector< ::libs::helpers::files::FileNode >
get_list_dlls_as_libs ()
{
  std::vector< ::libs::helpers::files::FileNode > ret;
  ret.reserve (128);

  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vcodec_gen", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vcd_all2hsl", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vcd_all2rgb", 0, 0, 0 });

#if (U3_LIBS_ENABLE_DETECT_FACE_VDD == 1)
  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_detect_face", 0, 0, 0 });
#endif

  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_detect_move", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vfn_freq_domain", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vfn_space", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vfn_time", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_base_id", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vgd_vgen_conv3_11", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vgd_vgen_diff", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vgd_vgen_mops", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vsa_fixed", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vsa_flow", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vsd_gen_vgen", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vcorrect", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vgradient", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vhistogram", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vmatrix", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vsharper", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vdd_vtexter", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vut_vec2image", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vvd_vcodec_test", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vvd_vcodec_mjpg", 0, 0, 0 });

  ret.emplace_back (::libs::helpers::files::FileNode { "vss_desk_vgen", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_fake_vgen", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_pict_vgen", 0, 0, 0 });

#ifdef U3_OS_ANDROID
#  if defined(U3_USE_SOURCE_VSS_ANDROID_JAVA_VGEN)
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_android_java_vgen", 0, 0, 0 });
#  endif
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_android_vgen", 0, 0, 0 });
#endif

#ifdef U3_OS_RASPBERRY
  // ret.emplace_back (::libs::helpers::files::FileNode { "vss_rasp_vgen", 0, 0, 0 });
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_v4l2_vgen", 0, 0, 0 });
#endif

#ifdef U3_OS_WIN32_DESKTOP
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_dshow_vgen", 0, 0, 0 });
#endif

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_ORANGE_PI)
  ret.emplace_back (::libs::helpers::files::FileNode { "vss_v4l2_vgen", 0, 0, 0 });
#endif

  for (auto& file : ret)
  {
    file.name_ = ::libs::helpers::dlls::decorate_dll_name (file.name_);
    U3_XLOG_DEV ("get_list_dlls_as_libs find file in libs" + TOLOG (file.name_));
  }
  U3_XLOG_DEV ("get_list_dlls_as_libs" + VTOLOG (ret.size ()));
  return ret;
}
}   // namespace libs::proxy
