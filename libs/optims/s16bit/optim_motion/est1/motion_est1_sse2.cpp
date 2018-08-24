//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file     motion_est1_sse2.cpp
\author   Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date     28.08.2016
\project  uuu_optim_motion
\brief    Оценка движения в кадре.
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "motion_est1.hpp"
#include "mmedia/libs/optims/optim/mcalls/helpers/buff_helpers_functs.hpp"
#include "move_alg.hpp"

#if defined(UUU_CPU_X86)

namespace libs { namespace optim { namespace s16bit { namespace motion { namespace est1 {

void
sse2 (::libs::optim::MCallInfo& _info)
{
  return alu (_info);
}

}}}}}      // namespace libs::optim::s16bit::motion::est1

#endif
