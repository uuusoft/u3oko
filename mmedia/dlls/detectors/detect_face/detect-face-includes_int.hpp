#pragma once
/**
\file       detect-face-includes_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_detect_face
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"

#include "../../dlls-includes_int.hpp"

#ifndef U3_SKIP_DLIB
// debug
// #  define U3_SKIP_DLIB
#endif

#ifndef U3_SKIP_DLIB
#  include "dlib/image_processing/frontal_face_detector.h"
#  include "dlib/image_io.h"
#endif

#include "turbojpeg.h"   // debug
#include "mmedia/utils/dbufs/dbufs-includes.hpp"
#include "detect-face-syn.hpp"
#include "helpers/copy2dlib-helper-func.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3detectface          "
