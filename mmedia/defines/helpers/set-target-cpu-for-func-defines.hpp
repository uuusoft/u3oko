#pragma once
/**
\file       set-target-cpu-for-func-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.05.2018
\project    u3_defines
\brief      Определение для уточнения типа процессора, под который собирается конкретная функция.
*/

#ifndef U3_SET_TARGET_CPU

#  if defined(U3_COMPILER_MSC)
#    define U3_SET_TARGET_CPU(xcpu)
#  elif defined(U3_COMPILER_GNUC)
#    define U3_SET_TARGET_CPU(xcpu) [[gnu::target (#xcpu)]]
#  elif defined(U3_COMPILER_CLANG)
#    define U3_SET_TARGET_CPU(xcpu) [[gnu::target (#xcpu)]]
#  else
#    error "unknown compile"
#  endif

#endif
