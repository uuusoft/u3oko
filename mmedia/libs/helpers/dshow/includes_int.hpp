#pragma once
/**
\file       includes_int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2018
\project    u3_dshow_vgen
*/

#ifdef U3_OS_WIN32_DESKTOP
#  pragma warning(push)
#  pragma warning(disable : 4995)

#  include <dshow.h>
#  include <initguid.h>

#  include <strsafe.h>
#  include <evcode.h>
#  include <objbase.h>
#  include <uuids.h>
#  include <CrtDbg.h>
#  include <shlobj.h>
#  include <initguid.h>
#  include <Wininet.h>
#  include <shellapi.h>
#  include <initguid.h>
#  include <Wininet.h>
#  include <dvdmedia.h>

#  pragma warning(pop)

#endif

#include "includes.hpp"
