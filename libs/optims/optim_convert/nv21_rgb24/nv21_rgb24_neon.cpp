//This is an independent project of an individual developer. Dear PVS-Studio, please check it.
//PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/**
\file       nv21_rgb24_neon.cpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       14.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_gen_convert
\brief      empty brief
*/
#include "mmedia/defines/defines.hpp"
#include "mmedia/defines/includes.hpp"
#include "mmedia/libs/optims/optim_convert/includes_int.hpp"
#include "../includes_int.hpp"
#include "nv21_rgb24.hpp"
#include "nv21_rgb24_int.hpp"

#if defined(UUU_CPU_ARM)

namespace libs { namespace optim { namespace convert { namespace nv21_rgb24 {

void
neon (::libs::optim::MCallInfo& _info)
{
  NV212RGB24 (8);

  int16x8_t _const_16  = vdupq_n_s16 (16);
  int16x8_t _const_128 = vdupq_n_s16 (128);

  const int _mem_consts_red_uv[4] = { 0, 6537, 0, 6537 };
  int32x4_t _consts_red_uv        = vld1q_s32 (_mem_consts_red_uv);
  const int _mem_consts_red_vu[4] = { 6537, 0, 6537, 0 };
  int32x4_t _consts_red_vu        = vld1q_s32 (_mem_consts_red_vu);

  const int _mem_consts_green_uv[4] = { -1605, -3330, -1605, -3300 };
  int32x4_t _consts_green_uv        = vld1q_s32 (_mem_consts_green_uv);
  const int _mem_consts_green_vu[4] = { -3330, -1605, -3330, -1605 };
  int32x4_t _consts_green_vu        = vld1q_s32 (_mem_consts_green_vu);

  const int _mem_consts_blue_uv[4] = { 8391, 0, 8391, 0 };
  int32x4_t _consts_blue_uv        = vld1q_s32 (_mem_consts_blue_uv);
  const int _mem_consts_blue_vu[4] = { 0, 8391, 0, 8391 };
  int32x4_t _consts_blue_vu        = vld1q_s32 (_mem_consts_blue_vu);

  int32x4_t   _consts_4769 = vdupq_n_s32 (4769);
  uint8x8_t   _y8;
  uint8x8_t   _uv8;
  uint8x8_t   _vu8;
  int16x8_t   _y16;
  int16x8_t   _vu16;
  int16x8_t   _uv16;
  uint8x8x3_t _vrgb24;

  for (std::size_t indx_y = 0; indx_y < _yuy2->height_; ++indx_y)
    {
      const unsigned char* _prev_uv_buff = _uv_buff;

      for (std::size_t indx_x = 0; indx_x < _yuy2->width_; indx_x += _ppc)
        {
          _y8   = vld1_u8 (_y_buff);
          _uv8  = vld1_u8 (_uv_buff);
          _vu8  = vrev16_u8 (_uv8);
          _y16  = vreinterpretq_s16_u16 (vmovl_u8 (_y8));
          _vu16 = vreinterpretq_s16_u16 (vmovl_u8 (_vu8));
          _uv16 = vreinterpretq_s16_u16 (vmovl_u8 (_uv8));

          const int32x4_t _y32_low         = vsubl_s16 (vget_low_s16 (_y16), vget_low_s16 (_const_16));
          const int32x4_t _y32_high        = vsubl_s16 (vget_high_s16 (_y16), vget_high_s16 (_const_16));
          const int32x4_t _vu32_low        = vsubl_s16 (vget_low_s16 (_vu16), vget_low_s16 (_const_128));
          const int32x4_t _vu32_high       = vsubl_s16 (vget_high_s16 (_vu16), vget_high_s16 (_const_128));
          const int32x4_t _uv32_low        = vsubl_s16 (vget_low_s16 (_uv16), vget_low_s16 (_const_128));
          const int32x4_t _uv32_high       = vsubl_s16 (vget_high_s16 (_uv16), vget_high_s16 (_const_128));
          const int32x4_t _y32_premul_low  = vmulq_s32 (_y32_low, _consts_4769);
          const int32x4_t _y32_premul_high = vmulq_s32 (_y32_high, _consts_4769);

          //red
          int32x4_t _akk32_low  = vmlaq_s32 (_y32_premul_low, _vu32_low, _consts_red_vu);
          int32x4_t _akk32_high = vmlaq_s32 (_y32_premul_high, _vu32_high, _consts_red_vu);

          _akk32_low  = vmlaq_s32 (_akk32_low, _uv32_low, _consts_red_uv);
          _akk32_high = vmlaq_s32 (_akk32_high, _uv32_high, _consts_red_uv);

          _akk32_low  = vshrq_n_s32 (_akk32_low, 12);
          _akk32_high = vshrq_n_s32 (_akk32_high, 12);

          uint16x4_t _akk16_low  = vqmovun_s32 (_akk32_low);
          uint16x4_t _akk16_high = vqmovun_s32 (_akk32_high);

          _vrgb24.val[0] = vqmovn_u16 (vcombine_u16 (_akk16_low, _akk16_high));
          //_vrgb24.val[0]  = vdup_n_u8(255 );//debug

          //green
          _akk32_low  = vmlaq_s32 (_y32_premul_low, _vu32_low, _consts_green_vu);
          _akk32_high = vmlaq_s32 (_y32_premul_high, _vu32_high, _consts_green_vu);
          _akk32_low  = vmlaq_s32 (_akk32_low, _uv32_low, _consts_green_uv);
          _akk32_high = vmlaq_s32 (_akk32_high, _uv32_high, _consts_green_uv);

          _akk32_low  = vshrq_n_s32 (_akk32_low, 12);
          _akk32_high = vshrq_n_s32 (_akk32_high, 12);

          _akk16_low  = vqmovun_s32 (_akk32_low);
          _akk16_high = vqmovun_s32 (_akk32_high);

          _vrgb24.val[1] = vqmovn_u16 (vcombine_u16 (_akk16_low, _akk16_high));
          //_vrgb24.val[1]  = vdup_n_u8(0);//debug


          //blue
          _akk32_low  = vmlaq_s32 (_y32_premul_low, _vu32_low, _consts_blue_vu);
          _akk32_high = vmlaq_s32 (_y32_premul_high, _vu32_high, _consts_blue_vu);
          _akk32_low  = vmlaq_s32 (_akk32_low, _uv32_low, _consts_blue_uv);
          _akk32_high = vmlaq_s32 (_akk32_high, _uv32_high, _consts_blue_uv);

          _akk32_low  = vshrq_n_s32 (_akk32_low, 12);
          _akk32_high = vshrq_n_s32 (_akk32_high, 12);

          _akk16_low  = vqmovun_s32 (_akk32_low);
          _akk16_high = vqmovun_s32 (_akk32_high);

          _vrgb24.val[2] = vqmovn_u16 (vcombine_u16 (_akk16_low, _akk16_high));
          //_vrgb24.val[2]  = vdup_n_u8(0);//debug

          //store
          vst3_u8 (_rgb24_buff, _vrgb24);

          _y_buff += 8;
          _uv_buff += 8;
          _rgb24_buff += 24;
        }

      _y_buff += _leak_yuy2;
      _uv_buff += _leak_yuy2;
      _rgb24_buff += _leak_rgb24;

      if (_odd_line)
        {
          _uv_buff = _prev_uv_buff;
        }

      _odd_line = !_odd_line;
    }
  return;
}

}}}}      // namespace libs::optim::convert::nv21_rgb24

#endif
