//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       
*\author    Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
*\create    31.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
*\brief     Набор функция для конвертации L <---> RGB16
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"

#include "l_vs_rgb2.hpp"
#include "rgb_to_l_int2.hpp"

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace l_vs_rgb2 {

void
rgb24_to_l_alu (::libs::optim::MCallInfo& _info)
{
  RGB2L_PREFIX (1);

  _leak_hsl;      //workaround error C2220

  const std::size_t    _stride_hsl = _info.dsts_[0].stride_;
  const unsigned char* _rgb24str   = UUU_MEM_CAST<const unsigned char*> (_rgb24);

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; ++indx_x)
        {
          _l[indx_x] = ::libs::optim::convert::gen::rgb2y (_rgb24str[0], _rgb24str[1], _rgb24str[2]);

          _rgb24str += 3;
        }

      FAST_MOVE_CPTR (_rgb24str, _leak_rgb);
      FAST_MOVE_PTR (_l, _stride_hsl);
    }

  return;
}

}}}}}      // namespace libs::optim::s16bit::convert::l_vs_rgb2
