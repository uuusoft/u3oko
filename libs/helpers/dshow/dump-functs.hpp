#pragma once
/**
\file       dump-functs.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.07.2018
\copyright  www.uuusoft.com
\project    uuu_dshow_vgen
*/

namespace libs { namespace helpers { namespace dshow {

#if defined(UUU_OS_WIN32_DESKTOP)
std::string to_str_dword (const unsigned long _val);

std::string to_str_rect (const RECT* _rect);

std::string to_str_bi_compression (const unsigned long _val);

void dump (const BITMAPINFOHEADER* _info);

void dump (const VIDEOINFOHEADER* _info);

void dump (const VIDEOINFOHEADER2* _info);

void dump (const AM_MEDIA_TYPE* _minfo);

//void dump (const IPinPtr& _ipin);
#endif

}}}      // namespace libs::helpers::dshow
