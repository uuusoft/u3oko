//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       ycb_rgb24_alu.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       30.07.2018
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "mmedia/libs/optims/optim_convert/gen/yuy2_rgb_gen.hpp"
#include "ycb_rgb24.hpp"
#include "ycb_rgb24_int.hpp"

namespace libs { namespace optim { namespace convert { namespace ycb_rgb24 {

void
alu (::libs::optim::MCallInfo& _info)
{
  YCB2RGB24_PREFIX;
  XULOG_TRACE ("::libs::optim::convert::ycb_rgb24::alu: beg, width=" << _width << ", height=" << _height);

#if 0
  const int            _size_block = _height * _width;
  const unsigned char* _y          = _yuy2_buff;
  const unsigned char* _rc         = _y + _size_block;
  const unsigned char* _rb         = _rc + _size_block;

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += 2)
        {
          short     _y1        = _y[0];      //UUU_ICAST_SHORT (_y[0]) - 16;
          short     _y2        = _y[1];      //UUU_ICAST_SHORT (_y[1]) - 16;
          short     _u         = UUU_ICAST_SHORT (_rc[0]) - 128;
          short     _v         = UUU_ICAST_SHORT (_rb[0]) - 128;
          const int _y1_premul = _y1 * 4769;

          _rgb24_buff[0] = gen::short2char (gen::yuv2red (_y1_premul, _u, _v));
          _rgb24_buff[1] = gen::short2char (gen::yuv2green (_y1_premul, _u, _v));
          _rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y1_premul, _u, _v));

          _rgb24_buff[0] = _y1;      // debug
          _rgb24_buff[1] = _y1;      // debug
          _rgb24_buff[2] = _y1;      // debug

          //_rgb24_buff[0] = rand () % 256;      // debug
          //_rgb24_buff[1] = rand () % 256;      // debug
          //_rgb24_buff[2] = rand () % 256;      // debug

          _rgb24_buff += 3;

          const int _y2_premul = _y2 * 4769;

          _rgb24_buff[0] = gen::short2char (gen::yuv2red (_y2_premul, _u, _v));
          _rgb24_buff[1] = gen::short2char (gen::yuv2green (_y2_premul, _u, _v));
          _rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y2_premul, _u, _v));

          _rgb24_buff[0] = _y2;      // debug
          _rgb24_buff[1] = _y2;      // debug
          _rgb24_buff[2] = _y2;      // debug

          //_rgb24_buff[0] = rand () % 256;      // debug
          //_rgb24_buff[1] = rand () % 256;      // debug
          //_rgb24_buff[2] = rand () % 256;      // debug

          _y += 4;
          ++_rc;
          ++_rb;
          _rgb24_buff += 3;
        }

      //_yuy2_buff += _leak_yuy2;
      _rgb24_buff += _leak_rgb24;
    }
#elif 1
  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += 2)
        {
          short _y1 = _yuy2_buff[0];      //UUU_ICAST_SHORT (_yuy2_buff[0]) - 16;
          short _y2 = _yuy2_buff[1];      //UUU_ICAST_SHORT (_yuy2_buff[2]) - 16;
          //short     _u         = UUU_ICAST_SHORT (_yuy2_buff[2]) - 128;
          //short     _v         = UUU_ICAST_SHORT (_yuy2_buff[1]) - 128;
          //const int _y1_premul = _y1 * 4769;

          //_rgb24_buff[0] = gen::short2char (gen::yuv2red (_y1_premul, _u, _v));
          //_rgb24_buff[1] = gen::short2char (gen::yuv2green (_y1_premul, _u, _v));
          //_rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y1_premul, _u, _v));

          _rgb24_buff[0] = _y1;      // debug
          _rgb24_buff[1] = _y1;      // debug
          _rgb24_buff[2] = _y1;      // debug
          _rgb24_buff += 3;

          _rgb24_buff[0] = _y2;      // debug
          _rgb24_buff[1] = _y2;      // debug
          _rgb24_buff[2] = _y2;      // debug
          _rgb24_buff += 3;

          //_rgb24_buff[0] = rand () % 256;      // debug
          //_rgb24_buff[1] = rand () % 256;      // debug
          //_rgb24_buff[2] = rand () % 256;      // debug

          _yuy2_buff += 2;
        }

      _yuy2_buff += _leak_yuy2;
      _rgb24_buff += _leak_rgb24;
    }

#else
  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += 2)
        {
          short     _y1        = UUU_ICAST_SHORT (_yuy2_buff[0]) - 16;
          short     _y2        = UUU_ICAST_SHORT (_yuy2_buff[2]) - 16;
          short     _u         = UUU_ICAST_SHORT (_yuy2_buff[3]) - 128;
          short     _v         = UUU_ICAST_SHORT (_yuy2_buff[1]) - 128;
          const int _y1_premul = _y1 * 4769;

          _rgb24_buff[0] = gen::short2char (gen::yuv2red (_y1_premul, _u, _v));
          _rgb24_buff[1] = gen::short2char (gen::yuv2green (_y1_premul, _u, _v));
          _rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y1_premul, _u, _v));

          _rgb24_buff[0] = rand () % 256;      // debug
          _rgb24_buff[1] = rand () % 256;      // debug
          _rgb24_buff[2] = rand () % 256;      // debug

          _rgb24_buff += 3;

          const int _y2_premul = _y2 * 4769;

          _rgb24_buff[0] = gen::short2char (gen::yuv2red (_y2_premul, _u, _v));
          _rgb24_buff[1] = gen::short2char (gen::yuv2green (_y2_premul, _u, _v));
          _rgb24_buff[2] = gen::short2char (gen::yuv2blue (_y2_premul, _u, _v));

          //_rgb24_buff[0] = rand () % 256;      // debug
          //_rgb24_buff[1] = rand () % 256;      // debug
          //_rgb24_buff[2] = rand () % 256;      // debug

          _yuy2_buff += 4;
          _rgb24_buff += 3;
        }

      _yuy2_buff += _leak_yuy2;
      _rgb24_buff += _leak_rgb24;
    }
#endif
  XULOG_TRACE ("::libs::optim::convert::yuy2_rgb24::alu: end");
  return;
}

}}}}      // namespace libs::optim::convert::ycb_rgb24
