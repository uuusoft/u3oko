/**
\file       flip_y_avx1.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_block
\brief      Функии для зеркального обображения массивов по вертикали
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "flip_y.hpp"
#include "flip_y_move_alg.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::block::flip_y
{
struct TFlipperAVX1 final {
  TFlipperAVX1 ()
  {
  }

  void
  init (TParams& params)
  {
  }

  U3_SET_TARGET_CPU (avx)
  void
  update (std::uint8_t* str1, std::uint8_t* str2)
  {
    __m256i temp1;
    __m256i temp2;

    temp1 = _mm256_load_si256 (U3_CAST_REINTERPRET< __m256i* > (str1));
    temp2 = _mm256_load_si256 (U3_CAST_REINTERPRET< __m256i* > (str2));

    _mm256_store_si256 (U3_CAST_REINTERPRET< __m256i* > (str1), temp2);
    _mm256_store_si256 (U3_CAST_REINTERPRET< __m256i* > (str2), temp1);
  }
};


U3_SET_TARGET_CPU (avx)
void
avx1 (::libs::optim::io::MCallInfo& info)
{
  _mm256_zeroupper ();
  move_alg< TFlipperAVX1, 32 > (info);
  _mm256_zeroupper ();
}
}   // namespace libs::optim::s16bit::block::flip_y

#endif
