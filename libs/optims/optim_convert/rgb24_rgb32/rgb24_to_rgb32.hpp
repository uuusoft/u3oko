#pragma once
/**
\file       rgb24_to_rgb32.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace convert { namespace rgb24_rgb32 {
/**
  \brief  empty brief
  */
void alu (
  const unsigned char* rgb24_buff,
  unsigned int         stride_rgb24,
  unsigned int         width,
  unsigned int         height,
  unsigned char*       rgb32_buff,
  unsigned int         stride_rgb32,
  unsigned int         max_size_buff_rgb32,
  unsigned char        fill_alpha = 0);

}}}}      // namespace libs::optim::convert::rgb24_rgb32
