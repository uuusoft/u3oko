//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       defines_tstring.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
#if !defined(DEFINE_TCHAR_MACROS)

#define DEFINE_TCHAR_MACROS

#if defined(UNICODE)
#define UUU_T(x) L##x
#define UUU_TCHAR wchar_t
#else
#define UUU_T(x) x
#define UUU_TCHAR char
#endif

#endif


#if defined(UNICODE)
using tstring       = std::wstring;
using tstringstream = std::wstringstream;
using tofstream     = std::wofstream;
using tformat       = boost::wformat;
#else
using tstring       = std::string;
using tstringstream = std::stringstream;
using tofstream     = std::ofstream;
using tformat       = boost::format;
#endif
