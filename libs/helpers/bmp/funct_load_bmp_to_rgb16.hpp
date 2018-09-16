#pragma once
/**
\file       funct_load_bmp_to_s16bit.hpp
\brief      Function for load data from bmp32 file and convert to r16g16b16 format
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       26.07.2016
\copyright  www.uuusoft.com
\project    uuu_helpers
\brief    
*/
//  old shit
namespace libs { namespace helpers { namespace bmp {
#if 0
  /**
  \brief  empty brief
  */
  bool load_bmp_to_s16bit (
    ::libs::optim::s16bit::convert::rgb32_rgb48_funct convert_funct,
    ::libs::optim::funct_mcall_type               mirror_funct,
    const std::string&                  name_file,
    short**                       r16,
    short**                       g16,
    short**                       b16,
    int*                        width,
    int*                        height,
    int*                        stride_byte,
    int                         need_div_stride_byte,
    int*                        max_size_buffer);
#endif
}}}      // namespace libs::helpers::bmp
