/**
\file       convolutions_expand.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       26.07.2016
\project    u3_optim_conv
\brief      свертка буфера с маской заданного размера
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"

#undef MODUL_2D_CONV_IMPL
#include "cond_3x3.cxx"
#include "cond_3x3_alu.cxx"
#include "cond_3x3_sse2.cxx"
#include "cond_3x3_avx1.cxx"
#include "cond_3x3_avx2.cxx"


#define MODUL_2D_CONV_IMPL
#include "cond_3x3.cxx"
#include "cond_3x3_alu.cxx"
#include "cond_3x3_sse2.cxx"
#include "cond_3x3_avx1.cxx"
#include "cond_3x3_avx2.cxx"
#undef MODUL_2D_CONV_IMPL
