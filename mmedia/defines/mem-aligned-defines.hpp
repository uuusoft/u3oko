#pragma once
/**
\file       mem-aligned-defines.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_defines
\brief      Обявление спецификаторов памяти, общих для всей системы.
*/

#if defined(U3_CPU_X86)

#  if defined(U3_CPU_X86_32)
#    define U3_ALIGN_DEFAULT alignas (4)
#  else
#    define U3_ALIGN_DEFAULT alignas (8)
#  endif

#elif defined(U3_CPU_ARM)

#  if defined(U3_CPU_ARM_8)
#    define U3_ALIGN_DEFAULT alignas (8)
#  else
#    define U3_ALIGN_DEFAULT alignas (4)
#  endif

#else
#  error select OS
#endif
