/**
\file       iproperties-proxy.hpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "iproperties-proxy.hpp"

namespace libs::proxy
{
auto
get_list_dlls_as_libs () -> std::vector< ::libs::utility::files::FileNode >
{
  std::vector< ::libs::utility::files::FileNode > ret;
  ret.reserve (128);

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vcodec_gen", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vcd_all2hsl", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vcd_all2rgb", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

#if (U3_LIBS_ENABLE_DETECT_FACE_VDD == 1)
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_detect_face", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
#endif

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_detect_move", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vfn_freq_domain", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vfn_space", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vfn_time", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_base_id", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vgd_vgen_conv3_11", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vgd_vgen_diff", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vgd_vgen_mops", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vsa_fixed", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vsa_flow", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vsd_gen_vgen", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vcorrect", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vgradient", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vhistogram", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vmatrix", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vsharper", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vdd_vtexter", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vut_vec2image", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vvd_vcodec_test", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vvd_vcodec_mjpg", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vvd_vcodec_x264", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vss_desk_vgen", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vss_fake_vgen", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vss_pict_vgen", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });

#ifdef U3_OS_ANDROID
#  if defined(U3_USE_SOURCE_VSS_ANDROID_JAVA_VGEN)
  ret.emplace_back (::libs::utility::files::FileNode { "vss_android_java_vgen", 0, 0, 0 });
#  endif
  ret.emplace_back (::libs::utility::files::FileNode { "vss_android_vgen", 0, 0, 0 });
#endif

#ifdef U3_OS_RASPBERRY
  // ret.emplace_back (::libs::utility::files::FileNode { "vss_rasp_vgen", 0, 0, 0 });
#endif

#ifdef U3_OS_WIN32_DESKTOP
  ret.emplace_back (::libs::utility::files::FileNode { "vss_dshow_vgen", 0, 0, 0 });
#endif

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_ORANGE_PI) || defined(U3_OS_RASPBERRY)
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vss_v4l2_vgen", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
  ret.emplace_back (::libs::utility::files::FileNode { .name_ = "vvd_vcodec_va", .create_time_ = 0, .last_write_time_ = 0, .size_ = 0 });
#endif

  for (auto& file : ret)
  {
    file.name_ = ::libs::utility::dlls::decorate_dll_name (file.name_);
    U3_XLOG_DBG ("get_list_dlls_as_libs find file in libs" + TOLOG (file.name_));
  }
  U3_XLOG_DBG ("get_list_dlls_as_libs" + VTOLOG (ret.size ()));
  return ret;
}
}   // namespace libs::proxy
