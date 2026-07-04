/**
\file       codepage-convert-funcs.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_helpers_lib
*/
#include "../utility-lib-includes_int.hpp"

namespace libs::utility::strings
{
auto
wstring2utf8 (const std::wstring& str) -> std::string
{
  const std::string ret = std::wstring_convert< std::codecvt_utf8< wchar_t >, wchar_t > {}.to_bytes (str);
  // const std::string aname_filter = boost::locale::conv::from_utf (name_filter, "UTF-8");
  return ret;
}
}   // namespace libs::utility::strings
