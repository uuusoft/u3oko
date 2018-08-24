#pragma once
/**
\file       includes_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.07.2018
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/
#if defined(UUU_OS_WIN32_DESKTOP)
#pragma warning(push)
#pragma warning(disable : 4995)

#include <d3d8.h>
#include <dshow.h>
#include <initguid.h>

#include <strsafe.h>
#include <evcode.h>
#include <objbase.h>
#include <uuids.h>
#include <CrtDbg.h>
#include <shlobj.h>
#include <initguid.h>
#include <Wininet.h>
#include <shellapi.h>
#include <initguid.h>
#include <Wininet.h>
#include <dvdmedia.h>

#pragma warning(pop)

#endif

#include "includes.hpp"
