#pragma once
/**
\file       dump-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2018
\project    u3_dshow_vgen
*/

#ifdef U3_OS_WIN32_DESKTOP

namespace libs::helpers::dshow
{
std::string to_str_dword (const unsigned long val);
std::string to_str_rect (const RECT* rect);
std::string to_str_bi_compression (const unsigned long val);
void        dump (const BITMAPINFOHEADER* info);
void        dump (const VIDEOINFOHEADER* info);
void        dump (const VIDEOINFOHEADER2* info);
void        dump (const AM_MEDIA_TYPE* minfo);
}   // namespace libs::helpers::dshow

#endif
