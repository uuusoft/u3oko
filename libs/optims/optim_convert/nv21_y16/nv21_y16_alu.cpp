//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       nv21_y16_alu.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "nv21_y16.hpp"
#include "nv21_y16_int.hpp"

namespace libs { namespace optim { namespace convert { namespace nv21_y16 {

void
alu (::libs::optim::MCallInfo& _info)
{
  NV212Y16_PREFIX (1);

  _leak_y16;      //workaround
  _leak_y8;       //workaround

  for (std::size_t _indxy = 0; _indxy < _height; ++_indxy)
    {
      for (std::size_t _indxx = 0; _indxx < _width; _indxx += _ppc)
        {
          _y16_buff[_indxx] = _y8_buff[_indxx];
          //_y16_buff[_indxx] = UUU_ICAST_SHORT(_indxx);//debug
        }

      FAST_MOVE_CPTR (_y8_buff, _stride_y8);
      FAST_MOVE_PTR (_y16_buff, _stride_y16);
    }

  return;
}

}}}}      // namespace libs::optim::convert::nv21_y16
