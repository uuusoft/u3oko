//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       x8_x16_avx2.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "x8_x16.hpp"
#include "x8_x16_int.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace convert { namespace x8_x16 {

UUU_SET_TARGET_CPU (avx2)
void
avx2 (::libs::optim::MCallInfo& _info)
{
#if 1
  return alu (_info);
#else
  X16_TO_X8_PREFIX (16);

  _mm256_zeroupper ();

  const __m256i _mask = _mm256_setr_epi16 (
    0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF, 0x00FF);

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += _ppc)
        {
          __m256i _data = _mm256_load_si256 (UUU_MEM_CAST<const __m256i*> (_yuy2_buff));

          _data = _mm256_and_si256 (_data, _mask);

          _mm256_store_si256 (UUU_MEM_CAST<__m256i*> (_y16_buff), _data);

          _yuy2_buff += _dppc;
          _y16_buff += _ppc;
        }

      FAST_MOVE_CPTR (_yuy2_buff, _leak_yuy2);
      FAST_MOVE_PTR (_y16_buff, _leak_y16);
    }

  _mm256_zeroupper ();
#endif
  return;
}

}}}}      // namespace libs::optim::convert::x8_x16

#endif
