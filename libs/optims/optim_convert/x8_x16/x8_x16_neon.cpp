//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       x8_x16_neon.cpp
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

#if defined(UUU_CPU_ARM)

namespace libs { namespace optim { namespace convert { namespace x8_x16 {

UUU_SET_TARGET_CPU (neon)
void
neon (::libs::optim::MCallInfo& _info)
{
#if 1
  return alu (_info);
#else
  X16_TO_X8_PREFIX (8);

  const int16x8_t _mask = vdupq_n_s16 (0x00FF);

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += _ppc)
        {
          int16x8_t _data = vld1q_s16 (UUU_MEM_CAST<const short*> (_yuy2_buff));

          _data = vandq_s16 (_data, _mask);

          vst1q_s16 (_y16_buff, _data);

          _yuy2_buff += _dppc;
          _y16_buff += _ppc;
        }

      FAST_MOVE_CPTR (_yuy2_buff, _leak_yuy2);
      FAST_MOVE_PTR (_y16_buff, _leak_y16);
    }
#endif
  return;
}

}}}}      // namespace libs::optim::convert::x8_x16

#endif
