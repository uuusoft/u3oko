//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    31.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     Набор функций для конвертации L <---> RGB16 через ALU
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "l_vs_rgb2.hpp"
#include "l_to_rgb_int2.hpp"

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb2 {

void
l_to_rgb24_alu (::libs::optim::MCallInfo& _info)
{
  L2RGB_PREFIX (1);

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          const unsigned char _val = static_cast<unsigned char> (_l[0] & 0xFF);

          _rgb24[0] = _val;
          _rgb24[1] = _val;
          _rgb24[2] = _val;

          ++_l;
          _rgb24 += 3;
        }

      FAST_MOVE_PTR (_rgb24, _leak_l);
      FAST_MOVE_CPTR (_l, _leak_l);
    }
  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb2
