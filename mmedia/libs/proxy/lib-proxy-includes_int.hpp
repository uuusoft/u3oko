#pragma once
/**
\file       lib-proxy-includes_int.hpp
\date       15.04.2022
\author     Erashov Anton erashov2026@proton.me
\project    u3_proxy_libs
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
#define U3_FILE_LOG_TAG "u3libproxy         "
