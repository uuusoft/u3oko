#pragma once
/**
\file       defines-detect-compiler-type.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Выводим определение компилятора системы
*/

#ifndef U3_COMPILER_MSC
#  if defined(_MSC_VER)
#    define U3_COMPILER_MSC
#  endif
#endif

#ifndef U3_COMPILER_GNUC
#  if defined(__clang__)
#    define U3_COMPILER_CLANG
#  endif
#endif

#ifndef U3_COMPILER_CLANG
#  if defined(__GNUC__)
#    define U3_COMPILER_GNUC
#  endif
#endif
