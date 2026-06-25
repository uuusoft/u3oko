#pragma once
/**
\file       desk-vgen-includes_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_desk_vgen
*/
#include "../../../dlls-includes_int.hpp"

#include "mmedia/dlls/sources/vgen_lib/gen-lib-includes.hpp"
#include "desk-vgen-syn.hpp"
#include "desk-vgen-includes.hpp"
#include "consts/desk-vgen-const-vals.hpp"
#include "icapture-desk-impl.hpp"
#include "impls/win32/capture-desk-impl-win32.hpp"
#include "impls/linux/x11/capture-desk-impl-linux-x11.hpp"
#include "impls/linux/wayland/capture-desk-impl-linux-wl.hpp"
#include "impls/mac/capture-desk-impl-mac.hpp"
#include "impls/android/capture-desk-impl-android.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3deskvgen            "
