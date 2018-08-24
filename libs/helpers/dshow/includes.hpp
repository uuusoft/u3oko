#pragma once
/**
\file       includes.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.07.2018
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/
#if defined(UUU_OS_WIN32_DESKTOP)

//  forward
struct _AMMediaType;
struct tagVIDEOINFOHEADER;
struct tagVIDEOINFOHEADER2;
struct tagBITMAPINFOHEADER;

using RECT             = tagRECT;
using AM_MEDIA_TYPE    = _AMMediaType;
using VIDEOINFOHEADER2 = tagVIDEOINFOHEADER2;
using VIDEOINFOHEADER  = tagVIDEOINFOHEADER;
using BITMAPINFOHEADER = tagBITMAPINFOHEADER;

#include "consts/vals.hpp"
#include "com-ptr.hpp"
#include "dshow_interfaces.hpp"
#include "interf_ptrs.hpp"
#include "convert-format-functs.hpp"
#include "dump-functs.hpp"

#endif
