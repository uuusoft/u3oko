#pragma once
/**
\file       libs-iproperties-includes_int.hpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_iproperties_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/ilink/consts/libs-ilink-const-vals.hpp"
#include "mmedia/libs/events/includes.hpp"
#include "mmedia/libs/link/libs-link-includes.hpp"
#include "mmedia/libs/core/libs-cores-core-includes.hpp"
#include "mmedia/libs/events_base/events-base-includes.hpp"
#include "mmedia/libs/properties/libs-properties-includes.hpp"

#include "mmedia/libs/optims/optim/io/libs-optims-optim-io-includes.hpp"
#include "mmedia/libs/optims/optim/mcalls/libs-optims-optim-mcalls-includes.hpp"

#include "mmedia/libs/proxy/proxy/ioptim-proxy.hpp"
#include "mmedia/libs/proxy/proxy/ievents-proxy.hpp"

#include "libs-iproperties-includes.hpp"

#ifdef U3_OS_WIN32_DESKTOP
#  include <Shlobj.h>
#endif

#undef U3_FILE_LOG_TAG
#define U3_FILE_LOG_TAG "u3iproperties         "
