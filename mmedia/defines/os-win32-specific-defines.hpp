#pragma once
/**
\file       os-win32-specific-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
*/

#ifdef U3_COMPILER_MSC

// Windows 8.1
#  define _WIN32_WINNT 0x0603

#  pragma warning(disable : 4752)
#  pragma warning(disable : 4190)
#  pragma warning(disable : 4316)
#  pragma warning(disable : 4459)

//  workaround vs2013/2015/2017
#  ifndef NOMINMAX
#    define NOMINMAX
#  endif

#  ifdef max
#    undef max
#  endif

#  ifdef min
#    undef min
#  endif

#  if defined(xor)
#    undef xor
#  endif

#else
#  ifndef __stdcall
#    define __stdcall
#  endif
#endif
