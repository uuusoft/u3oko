#pragma once
/**
\file       defines_tstring.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/
// old shit
#if defined(UNICODE)

#  define U3T(u3def_param) L##u3def_param

using tstring       = std::wstring;
using tstringstream = std::wstringstream;
using tofstream     = std::wofstream;
using tformat       = boost::wformat;

#else

#  define U3T(u3def_param) u3def_param

using tstring       = std::string;
using tstringstream = std::stringstream;
using tofstream     = std::ofstream;
using tformat       = boost::format;

#endif
