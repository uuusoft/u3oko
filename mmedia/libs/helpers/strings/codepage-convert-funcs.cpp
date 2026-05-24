/**
\file       codepage-convert-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_helpers_lib
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "../helpers-lib-includes_int.hpp"

namespace libs::helpers::strings
{
std::string
wstring2utf8 (const std::wstring& str)
{
  const std::string ret = std::wstring_convert< std::codecvt_utf8< wchar_t >, wchar_t > {}.to_bytes (str);
  // const std::string aname_filter = boost::locale::conv::from_utf (name_filter, "UTF-8");
  return ret;
}
}   // namespace libs::helpers::strings
