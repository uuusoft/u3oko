/**
\file       vcodec-mjpg-main.cpp:18:80
\author     Erashov Anton erashov2026@proton.me
\date       26.07.2016
\project    u3_vcodec_mjpg
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "vcodec-mjpg-includes_int.hpp"
#include "mjpeg-impl.hpp"

U3_CODEC_CREATE_FUNCT_EXTERN (vvd_vcodec_mjpg, ::dlls::codecs::vcodec_mjpg::MjpegImpl)
U3_CODEC_DELETE_FUNCT_EXTERN (vvd_vcodec_mjpg, ::dlls::codecs::vcodec_mjpg::MjpegImpl)

extern "C" BOOST_SYMBOL_EXPORT void
get_codec_info_vvd_vcodec_mjpg (libs::helpers::uids::minor::id_val guids[4])
{
  constexpr std::array< libs::helpers::uids::minor::id_val, 4 > temp = {
    libs::helpers::uids::minor::id_val::mjpeg,
    libs::helpers::uids::minor::id_val::unknown,
    libs::helpers::uids::minor::id_val::unknown,
    libs::helpers::uids::minor::id_val::unknown
  };
  std::copy (temp.begin (), temp.end (), guids);
}
