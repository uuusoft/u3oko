#pragma once
/**
\file       convert-format-funcs.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.07.2018
\project    u3_dshow_vgen
*/

#ifdef U3_OS_WIN32_DESKTOP

namespace libs::helpers::dshow
{
void convert2format (const ::libs::helpers::uids::minor::id_val&, const std::int32_t, const std::int32_t, const std::int32_t, VIDEOINFOHEADER*);
void convert2format (const ::libs::helpers::uids::minor::id_val&, const std::int32_t, const std::int32_t, const std::int32_t, VIDEOINFOHEADER2*);
#  if 0
unsigned long guid2dword_compression (const utils::cuuid& guid);
utils::cuuid dword_compression2guid (const unsigned long val, const BITMAPINFOHEADER* bmp);
#  endif
}   // namespace libs::helpers::dshow

#endif
