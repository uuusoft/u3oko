/**
\file       vcodec-x264-main.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       23.08.2018
\project    u3_vcodec_x264
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "includes_int.hpp"
#include "vcodec-x264-impl.hpp"

U3_CODEC_CREATE_FUNCT_EXTERN (vvd_vcodec_x264, ::dlls::codecs::vcodec_x264::x264Impl)
U3_CODEC_DELETE_FUNCT_EXTERN (vvd_vcodec_x264, ::dlls::codecs::vcodec_x264::x264Impl)

extern "C" BOOST_SYMBOL_EXPORT void
get_codec_info_vvd_vcodec_x264 (libs::helpers::uids::minor::id_val guids[4])
{
  constexpr std::array< libs::helpers::uids::minor::id_val, 4 > temp = {
    libs::helpers::uids::minor::id_val::x264,
    libs::helpers::uids::minor::id_val::unknown,
    libs::helpers::uids::minor::id_val::unknown,
    libs::helpers::uids::minor::id_val::unknown
  };
  std::copy (temp.begin (), temp.end (), guids);
}
