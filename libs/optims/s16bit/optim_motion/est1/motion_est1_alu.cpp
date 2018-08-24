//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file     motion_est1_alu.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date     28.08.2016
\project  uuu_optim_motion
\brief    Оценка движения
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buff_helpers_functs.hpp"
#include "move_alg.hpp"

namespace libs { namespace optim { namespace s16bit { namespace motion { namespace est1 {
/**
  \brief  empty brief
  */
struct TAluCalcObj
{
  TAluCalcObj ()
  {}

  void
  init (::libs::optim::MCallInfo& _info)
  {}

  int
  get_res (
    const short*      _src1,
    const short*      _src2,
    const short       _size_block,
    const std::size_t _stride)
  {
    int _ret = 0;

    for (std::size_t _indxy = 0; _indxy < UUU_ICAST_SIZE_T (_size_block); ++_indxy)
      {
        for (std::size_t _indxx = 0; _indxx < UUU_ICAST_SIZE_T (_size_block); ++_indxx)
          {
            int _iret = _src1[_indxx] - _src2[_indxx];
            _ret += std::abs (_iret);      //SAD
            //_ret+= _iret * _iret;   //SSD
          }

        FAST_MOVE_CPTR (_src1, _stride);
        FAST_MOVE_CPTR (_src2, _stride);
      }

    return _ret;
  }
};


void
alu (::libs::optim::MCallInfo& _info)
{
  return move_alg<TAluCalcObj> (_info);
}

}}}}}      // namespace libs::optim::s16bit::motion::est1
