//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       rgb24_to_rgb32.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "rgb24_to_rgb32.hpp"

namespace libs { namespace optim { namespace convert { namespace rgb24_rgb32 {

void
alu (
  const unsigned char* rgb24_buff,
  unsigned int         stride_rgb24,
  unsigned int         width,
  unsigned int         height,
  unsigned char*       rgb32_buff,
  unsigned int         stride_rgb32,
  unsigned int         max_size_buff_rgb32,
  unsigned char        fill_alpha)
{
  UASSERT (rgb24_buff);
  UASSERT (stride_rgb24);
  UASSERT (width);
  UASSERT (height);
  UASSERT (rgb32_buff);
  UASSERT (stride_rgb32);
  UASSERT (max_size_buff_rgb32);
  UASSERT (width * 3 <= stride_rgb24);
  UASSERT (width * 4 <= stride_rgb32);
  UASSERT (stride_rgb32 * height <= max_size_buff_rgb32);

  const unsigned int _leak_rgb32 = stride_rgb32 - width * 4;
  const unsigned int _leak_rgb24 = stride_rgb24 - width * 3;

  for (unsigned int indx_y = 0; indx_y < height; ++indx_y)
    {
      for (unsigned int indx_x = 0; indx_x < width; ++indx_x)
        {
          rgb32_buff[3] = fill_alpha;
          rgb32_buff[0] = rgb24_buff[0];
          rgb32_buff[1] = rgb24_buff[1];
          rgb32_buff[2] = rgb24_buff[2];

          rgb32_buff += 4;
          rgb24_buff += 3;
        }

      rgb24_buff += _leak_rgb24;
      rgb32_buff += _leak_rgb32;
    }

  return;
}

}}}}      // namespace libs::optim::convert::rgb24_rgb32
