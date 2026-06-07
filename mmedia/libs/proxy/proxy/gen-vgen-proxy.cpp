/**
\file       gen-vgen-proxy.cpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_proxy_libs
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "gen-vgen-proxy.hpp"

#ifdef U3_OS_ANDROID
#  if defined(U3_USE_SOURCE_VSS_ANDROID_JAVA_VGEN)
extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_android_java_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_android_java_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#  endif

extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_android_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_android_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#endif

#if (U3_LIBS_ENABLE_DESK_VGEN_VSS == 1)
extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_desk_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_desk_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#endif

extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_fake_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_fake_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);

#if defined(U3_OS_RASPBERRY)
#  if (U3_LIBS_ENABLE_RASPBERRY_OPENMAX_VGEN_VSS == 1)
extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_rasp_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_rasp_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#  endif
#endif

#ifdef U3_OS_WIN32_DESKTOP
#  if (U3_LIBS_ENABLE_WIN32_DSHOW_VGEN_VSS == 1)
extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_dshow_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_dshow_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#  endif
#endif


#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  if (U3_LIBS_ENABLE_PICT_VGEN_VSS == 1)
extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_pict_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_pict_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#  endif
#endif

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
extern "C" BOOST_SYMBOL_EXPORT bool get_source_vss_v4l2_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
extern "C" BOOST_SYMBOL_EXPORT bool free_source_vss_v4l2_vgen (::dlls::sources::gen_lib::ISourceImpl** obj);
#endif

namespace libs::proxy
{
::dlls::sources::gen_lib::bcreate_source_func_type
get_create_source_funct (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);

#ifdef U3_OS_ANDROID
#  if defined(U3_USE_SOURCE_VSS_ANDROID_JAVA_VGEN)
  if (lib_id == "vss_android_java_vgen")
  {
    return get_source_vss_android_java_vgen;
  }
#  endif

  if (lib_id == "vss_android_vgen")
  {
    return get_source_vss_android_vgen;
  }
#endif

#if (U3_LIBS_ENABLE_DESK_VGEN_VSS == 1)
  if (lib_id == "vss_desk_vgen")
  {
    return get_source_vss_desk_vgen;
  }
#endif

  if (lib_id == "vss_fake_vgen")
  {
    return get_source_vss_fake_vgen;
  }

#if defined(U3_OS_RASPBERRY)
#  if (U3_LIBS_ENABLE_RASPBERRY_OPENMAX_VGEN_VSS == 1)
  if (lib_id == "vss_rasp_vgen")
  {
    return get_source_vss_rasp_vgenn;
  }
#  endif
#endif

#ifdef U3_OS_WIN32_DESKTOP
#  if (U3_LIBS_ENABLE_WIN32_DSHOW_VGEN_VSS == 1)
  if (lib_id == "vss_dshow_vgen")
  {
    return get_source_vss_dshow_vgen;
  }
#  endif
#endif

#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  if (U3_LIBS_ENABLE_PICT_VGEN_VSS == 1)
  if (lib_id == "vss_pict_vgen")
  {
    return get_source_vss_pict_vgen;
  }
#  endif
#endif

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
  if (lib_id == "vss_v4l2_vgen")
  {
    return get_source_vss_v4l2_vgen;
  }
#endif

  U3_THROW_EXCEPTION ("failed function search" + TOLOG (lib_id));
}


::dlls::sources::gen_lib::bfree_source_func_type
get_free_source_funct (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);

#ifdef U3_OS_ANDROID
#  if defined(U3_USE_SOURCE_VSS_ANDROID_JAVA_VGEN)
  if (lib_id == "vss_android_java_vgen")
  {
    return free_source_vss_android_java_vgen;
  }
#  endif

  if (lib_id == "vss_android_vgen")
  {
    return free_source_vss_android_vgen;
  }
#endif

#if (U3_LIBS_ENABLE_DESK_VGEN_VSS == 1)
  if (lib_id == "vss_desk_vgen")
  {
    return free_source_vss_desk_vgen;
  }
#endif

  if (lib_id == "vss_fake_vgen")
  {
    return free_source_vss_fake_vgen;
  }

#if defined(U3_OS_RASPBERRY)
#  if (U3_LIBS_ENABLE_RASPBERRY_OPENMAX_VGEN_VSS == 1)
  if (lib_id == "vss_rasp_vgen")
  {
    return free_source_vss_rasp_vgen;
  }
#  endif
#endif

#ifdef U3_OS_WIN32_DESKTOP
#  if (U3_LIBS_ENABLE_WIN32_DSHOW_VGEN_VSS == 1)
  if (lib_id == "vss_dshow_vgen")
  {
    return free_source_vss_dshow_vgen;
  }
#  endif
#endif

#if defined(U3_OS_WIN32_DESKTOP) || defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
#  if (U3_LIBS_ENABLE_PICT_VGEN_VSS == 1)
  if (lib_id == "vss_pict_vgen")
  {
    return free_source_vss_pict_vgen;
  }
#  endif
#endif

#if defined(U3_OS_GNU_LINUX) || defined(U3_OS_RASPBERRY) || defined(U3_OS_ORANGE_PI)
  if (lib_id == "vss_v4l2_vgen")
  {
    return free_source_vss_v4l2_vgen;
  }
#endif

  U3_THROW_EXCEPTION ("failed function search" + TOLOG (lib_id));
}
}   // namespace libs::proxy
