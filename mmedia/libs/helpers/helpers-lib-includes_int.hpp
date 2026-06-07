#pragma once
/**
\file       helpers-lib-includes_int.hpp
\date       11.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/
#include "sys/isys-info.hpp"

#include "sys/cpu/x86/x86cpu_id.hpp"
#include "sys/cpu/mips/mipscpu_id.hpp"
#include "sys/cpu/arm/armcpu_id.hpp"

#include "sys/os/win32/sys-info-impl.hpp"
#include "sys/os/android/sys-info-impl.hpp"
#include "sys/os/lnux/sys-info-impl.hpp"
#include "sys/os/mac/sys-info-impl.hpp"

#include "dlls/freezer-dlls.hpp"

#include "../iproperties/appl_paths/libs-iproperties-appl-paths-includes.hpp"

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3libhelpers          "
