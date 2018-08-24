//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
#pragma once
/**
\file       include_intrunsic.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.05.2018
\copyright  www.uuusoft.com
\project    uuu_defines
*/
#if defined(UUU_COMPILER_MSC)

/* Microsoft C/C++-compatible compiler */
#include <intrin.h>
#include <mmintrin.h>

#elif (defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)) && defined(UUU_CPU_X86)

/* GCC-compatible compiler, targeting x86/x86-64 */
#include <x86intrin.h>
#include <immintrin.h>
#include <mmintrin.h>
#include <cpuid.h>

#elif (defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)) && defined(UUU_CPU_ARM)

#ifndef __ARM_NEON__
#define __ARM_NEON__
#endif

#ifndef __ARM_NEON
#define __ARM_NEON
#endif

/* GCC-compatible compiler, targeting ARM with NEON */
#include <arm_neon.h>

#elif (defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)) && defined(UUU_CPU_ARM) && defined(__IWMMXT__)

/* GCC-compatible compiler, targeting ARM with WMMX */
#include <mmintrin.h>

#elif (defined(UUU_COMPILER_GNUC) || defined(__xlC__) || defined(UUU_COMPILER_CLANG)) && defined(UUU_CPU_POWERPC) && (defined(__VEC__) || defined(__ALTIVEC__))

/* XLC or GCC-compatible compiler, targeting PowerPC with VMX/VSX */
#include <altivec.h>

#elif (defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)) && defined(UUU_CPU_POWERPC) && defined(__SPE__)

/* GCC-compatible compiler, targeting PowerPC with SPE */
#include <spe.h>

#endif
