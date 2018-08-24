//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       x8_x16_alu.cpp
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

namespace libs { namespace optim { namespace convert { namespace x8_x16 {

void
alu (::libs::optim::MCallInfo& _info)
{
  X8_TO_X16_PREFIX (1);

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += _ppc)
        {
          _x16_buff[0] = _x8_buff[0];
          //debug
          //_x16_buff[0] = 255;
          _x16_buff += _dppc;
          _x8_buff += _ppc;
        }

      FAST_MOVE_CPTR (_x8_buff, _leak_x8);
      FAST_MOVE_PTR (_x16_buff, _leak_x16);
    }

  return;
}

}}}}      // namespace libs::optim::convert::x8_x16
