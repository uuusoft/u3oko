//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       nv21_y16_neon.cpp
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

#if defined(UUU_CPU_ARM)

namespace libs { namespace optim { namespace convert { namespace nv21_y16 {

UUU_SET_TARGET_CPU (neon)
void
neon (::libs::optim::MCallInfo& _info)
{
  return alu (_info);
}

}}}}      // namespace libs::optim::convert::nv21_y16

#endif
