/**
\file       vcodec-gen-proxy.cpp
\date       17.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-gen-proxy.hpp"

#if defined(U3_LIBS_ENABLE_VCODEC_MJPG_VVD)
extern "C" BOOST_SYMBOL_EXPORT void create_codec_vvd_vcodec_mjpg (::dlls::codecs::codec_gen::CodecGeneric** pobj);
extern "C" BOOST_SYMBOL_EXPORT void delete_codec_vvd_vcodec_mjpg (::dlls::codecs::codec_gen::CodecGeneric* obj);
extern "C" BOOST_SYMBOL_EXPORT void get_codec_info_vvd_vcodec_mjpg (libs::helpers::uids::minor::id_val guids[4]);
#endif

#if defined(U3_LIBS_ENABLE_VCODEC_TEST_VVD)
extern "C" BOOST_SYMBOL_EXPORT void create_codec_vvd_vcodec_test (::dlls::codecs::codec_gen::CodecGeneric** pobj);
extern "C" BOOST_SYMBOL_EXPORT void delete_codec_vvd_vcodec_test (::dlls::codecs::codec_gen::CodecGeneric* obj);
extern "C" BOOST_SYMBOL_EXPORT void get_codec_info_vvd_vcodec_test (libs::helpers::uids::minor::id_val guids[4]);
#endif

#if defined(U3_LIBS_ENABLE_VCODEC_X264_VVD)
extern "C" BOOST_SYMBOL_EXPORT void create_codec_vvd_vcodec_x264 (::dlls::codecs::codec_gen::CodecGeneric** pobj);
extern "C" BOOST_SYMBOL_EXPORT void delete_codec_vvd_vcodec_x264 (::dlls::codecs::codec_gen::CodecGeneric* obj);
extern "C" BOOST_SYMBOL_EXPORT void get_codec_info_vvd_vcodec_x264 (libs::helpers::uids::minor::id_val guids[4]);
#endif

#if defined(U3_LIBS_ENABLE_VCODEC_VA_VVD)
extern "C" BOOST_SYMBOL_EXPORT void create_codec_vvd_vcodec_va (::dlls::codecs::codec_gen::CodecGeneric** pobj);
extern "C" BOOST_SYMBOL_EXPORT void delete_codec_vvd_vcodec_va (::dlls::codecs::codec_gen::CodecGeneric* obj);
extern "C" BOOST_SYMBOL_EXPORT void get_codec_info_vvd_vcodec_va (libs::helpers::uids::minor::id_val guids[4]);
#endif

namespace libs::proxy
{
dlls::codecs::vcodec_gen::funcs::func_get_codec_type
get_create_codec_func (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);

#if defined(U3_LIBS_ENABLE_VCODEC_MJPG_VVD)
  if (lib_id == "vvd_vcodec_mjpg")
  {
    return create_codec_vvd_vcodec_mjpg;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_TEST_VVD)
  if (lib_id == "vvd_vcodec_test")
  {
    return create_codec_vvd_vcodec_test;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_X264_VVD)
  if (lib_id == "vvd_vcodec_x264")
  {
    return create_codec_vvd_vcodec_x264;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_VA_VVD)
  if (lib_id == "vvd_vcodec_va")
  {
    return create_codec_vvd_vcodec_va;
  }
#endif

  U3_THROW_EXCEPTION ("find create codec funct" + TOLOG (lib_id));
}


dlls::codecs::vcodec_gen::funcs::func_free_codec_type
get_free_codec_func (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);

#if defined(U3_LIBS_ENABLE_VCODEC_MJPG_VVD)
  if (lib_id == "vvd_vcodec_mjpg")
  {
    return delete_codec_vvd_vcodec_mjpg;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_TEST_VVD)
  if (lib_id == "vvd_vcodec_test")
  {
    return delete_codec_vvd_vcodec_test;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_X264_VVD)
  if (lib_id == "vvd_vcodec_x264")
  {
    return delete_codec_vvd_vcodec_x264;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_VA_VVD)
  if (lib_id == "vvd_vcodec_va")
  {
    return delete_codec_vvd_vcodec_va;
  }
#endif

  U3_THROW_EXCEPTION ("find free codec funct" + TOLOG (lib_id));
}


dlls::codecs::vcodec_gen::funcs::func_codec_info_type
get_info_codec_func (const std::string& plib_id)
{
  const auto lib_id = libs::helpers::dlls::undecorate_dll_name (plib_id);

#if defined(U3_LIBS_ENABLE_VCODEC_MJPG_VVD)
  if (lib_id == "vvd_vcodec_mjpg")
  {
    return get_codec_info_vvd_vcodec_mjpg;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_TEST_VVD)
  if (lib_id == "vvd_vcodec_test")
  {
    return get_codec_info_vvd_vcodec_test ? ? ? ;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_X264_VVD)
  if (lib_id == "vvd_vcodec_x264")
  {
    return get_codec_info_vvd_vcodec_x264;
  }
#endif
#if defined(U3_LIBS_ENABLE_VCODEC_VA_VVD)
  if (lib_id == "vvd_vcodec_va")
  {
    return get_codec_info_vvd_vcodec_va;
  }
#endif

  U3_THROW_EXCEPTION ("find get info codec funct" + TOLOG (lib_id));
}
}   // namespace libs::proxy
