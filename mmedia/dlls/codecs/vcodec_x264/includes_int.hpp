#pragma once
/**
\file       includes_int.hpp
\date       23.08.2018
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_vcodec_x264
*/
#include "../../dlls-includes_int.hpp"

#include "mmedia/dlls/codecs/codec_funcs/codec-funcs-includes.hpp"
#include "mmedia/dlls/codecs/codec_funcs/bitgen/codec-funcs-bitgen-includes.hpp"
#include "mmedia/dlls/codecs/codec_gen/codec-gen-includes.hpp"

#include "vcodec-x264-syn.hpp"

#include "impls/ibase-h264-impl.hpp"
#include "impls/openh264/open-h264-impl.hpp"
#include "impls/x264/vcl-x264-impl.hpp"
#include "impls/factory-h264-impl.hpp"

#include "consts/vcodec-x264-const-vals.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3vcodec-x264         "
