/**
\file       flip_y_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_block
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "flip_y.hpp"
#include "flip_y_move_alg.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::block::flip_y
{
struct TFlipperSSE2 final {
  TFlipperSSE2 ()
  {
  }

  void
  init (TParams& _params)
  {
  }

  U3_SET_TARGET_CPU (sse2)
  void
  update (std::uint8_t* _str1, std::uint8_t* _str2)
  {
    __m128i _temp1;
    __m128i _temp2;

    _temp1 = _mm_load_si128 (U3_CAST_REINTERPRET< __m128i* > (_str1));
    _temp2 = _mm_load_si128 (U3_CAST_REINTERPRET< __m128i* > (_str2));

    _mm_store_si128 (U3_CAST_REINTERPRET< __m128i* > (_str1), _temp2);
    _mm_store_si128 (U3_CAST_REINTERPRET< __m128i* > (_str2), _temp1);
  }
};


U3_SET_TARGET_CPU (sse2)
void
sse2 (::libs::optim::io::MCallInfo& info)
{
  move_alg< TFlipperSSE2, 16 > (info);
}
}   // namespace libs::optim::s16bit::block::flip_y

#endif
