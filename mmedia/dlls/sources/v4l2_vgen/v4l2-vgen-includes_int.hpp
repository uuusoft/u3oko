#pragma once
/**
\file       v4l2-vgen-includes_int.hpp
\date       20.02.2026
\author     Erashov Anton erashov2026@proton.me
\project    u3_v4l2_vgen
*/
#include "../../dlls-includes_int.hpp"

#include "mmedia/dlls/sources/vgen_lib/gen-lib-includes.hpp"

#include <linux/videodev2.h>
#include <sys/ioctl.h>
#include <fcntl.h>

#include "V4l2Capture.h"
#include "logger.h"

#include "mmedia/dlls/codecs/codec_funcs/codec-funcs-includes.hpp"
#include "mmedia/dlls/codecs/codec_funcs/bitgen/codec-funcs-bitgen-includes.hpp"
#include "mmedia/dlls/codecs/codec_gen/codec-gen-includes.hpp"

#include "v4l2-vgen-syn.hpp"

#include "consts/v4l2-const-vals.hpp"
#include "helpers/v4l2-vgen-resource-holder.hpp"

#include "camera/v4l2-vgen-correct-image-interf.hpp"
#include "camera/v4l2-vgen-cam-impl.hpp"
#include "jpeg/v4l2-vgen-jpeg-codec-image-interf.hpp"
#include "jpeg/v4l2-vgen-jpeg-impl.hpp"
#include "video/v4l2-vgen-video-codec-interf.hpp"
#include "video/v4l2-vgen-video-impl.hpp"
#include "v4l2-vgen-source-impl.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3v4l2vgen            "
