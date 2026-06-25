#pragma once
/**
\file       includes.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.07.2018
\project    u3_dshow_vgen
*/
#ifdef U3_OS_WIN32_DESKTOP

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

#  include "consts/lib-helpers-dshow-const-vals.hpp"
#  include "com-ptr.hpp"
#  include "dshow_interfaces.hpp"
#  include "convert-format-funcs.hpp"
#  include "dump-funcs.hpp"

#endif
