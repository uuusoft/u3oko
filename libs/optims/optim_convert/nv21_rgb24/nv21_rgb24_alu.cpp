//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       nv21_rgb24_alu.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "nv21_rgb24.hpp"
#include "nv21_rgb24_int.hpp"

namespace libs { namespace optim { namespace convert { namespace nv21_rgb24 {

void
alu (::libs::optim::MCallInfo& _info)
{
  NV212RGB24 (2);

  for (std::size_t indx_y = 0; indx_y < _yuy2->height_; ++indx_y)
    {
      const unsigned char* _prev_uv_buff = _uv_buff;

      for (std::size_t indx_x = 0; indx_x < _yuy2->width_; indx_x += _ppc)
        {
          short _y1 = UUU_ICAST_SHORT (_y_buff[0]) - 16;
          short _y2 = UUU_ICAST_SHORT (_y_buff[1]) - 16;
          short _u  = UUU_ICAST_SHORT (_uv_buff[0]) - 128;
          short _v  = UUU_ICAST_SHORT (_uv_buff[1]) - 128;

          const int _y1_premul = _y1 * 4769;

          _rgb24_buff[0] = gen::short2char (gen::yuv2red (_y1_premul, _u, _v));
          _rgb24_buff[1] = gen::short2char (gen::yuv2green (_y1_premul, _u, _v));
          _rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y1_premul, _u, _v));

          _rgb24_buff += 3;

          const int _y2_premul = _y2 * 4769;

          _rgb24_buff[0] = gen::short2char (gen::yuv2red (_y2_premul, _u, _v));
          _rgb24_buff[1] = gen::short2char (gen::yuv2green (_y2_premul, _u, _v));
          _rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y2_premul, _u, _v));

          _y_buff += 2;
          _uv_buff += 2;
          _rgb24_buff += 3;
        }

      _y_buff += _leak_yuy2;
      _uv_buff += _leak_yuy2;

      if (_odd_line)
        {
          _uv_buff = _prev_uv_buff;
        }

      _rgb24_buff += _leak_rgb24;
      _odd_line = !_odd_line;
    }

  return;
}

}}}}      // namespace libs::optim::convert::nv21_rgb24
