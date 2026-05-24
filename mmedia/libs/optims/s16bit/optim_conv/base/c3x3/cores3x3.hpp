#pragma once
/**
\file       cores3x3.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "consts3x3.hpp"
#include "mmedia/libs/optims/s16bit/optim_conv/iconv-core.hpp"

namespace libs::optim::s16bit::conv::base::c3x3::cores
{
using values_core_type = IConvCore< std::int16_t, consts::align_size_core, consts::size_core >;

// clang-format off
const values_core_type all_1 = values_core_type (
  { 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type all_m1 = values_core_type (
  { 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type gaus1 = values_core_type (
  { 
    1,  2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    2,  4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1,  2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type gaus2 = values_core_type (
  { 
    1,  2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    2,  4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1,  2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type gaus3 = values_core_type (
  { 
    1,  2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    2,  4, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1,  2, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type laplas1 = values_core_type (
  { 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1,  8, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1, -1, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type laplas2 = values_core_type (
  { 
    0,  -1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1,  4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0,  -1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type laplas3 = values_core_type (
  { 
    0,  -1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    -1,  4, -1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    0,  -1,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type avg1 = values_core_type (
  { 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1, 8, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });

const values_core_type spot1 = values_core_type (
  { 
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 
    1, 9, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
  });
// clang-format on


inline void
copy (const std::vector< std::int16_t >& vals, values_core_type& mask)
{
  mask.fill (0);
  mask.load (vals);
}
}   // namespace libs::optim::s16bit::conv::base::c3x3::cores
