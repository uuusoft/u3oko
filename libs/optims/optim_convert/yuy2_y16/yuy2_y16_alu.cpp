//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       yuy2_y16_alu.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "yuy2_y16.hpp"
#include "yuy2_y16_int.hpp"

namespace libs { namespace optim { namespace convert { namespace yuy2_y16 {

void
alu (::libs::optim::MCallInfo& _info)
{
  YUY22Y16_PREFIX (2);

  for (std::size_t indx_y = 0; indx_y < _height; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < _width; indx_x += _ppc)
        {
          _y16_buff[0] = _yuy2_buff[0];
          _y16_buff[1] = _yuy2_buff[2];

          //debug
          //_y16_buff[0] = 255;
          //_y16_buff[0] = rand() % 256;
          //_y16_buff[1] = rand() % 256;
          //_y16_buff[0] = UUU_ICAST_INT( 2.0f * UUU_ICAST_FLOAT( indx_x ) / _width * 255 );
          //_y16_buff[1] = 255;//UUU_ICAST_INT( UUU_ICAST_FLOAT( indx_y ) / _height * 255 );

          _yuy2_buff += _dppc;
          _y16_buff += _ppc;
        }

      FAST_MOVE_CPTR (_yuy2_buff, _leak_yuy2);
      FAST_MOVE_PTR (_y16_buff, _leak_y16);
    }

  return;
}

}}}}      // namespace libs::optim::convert::yuy2_y16
