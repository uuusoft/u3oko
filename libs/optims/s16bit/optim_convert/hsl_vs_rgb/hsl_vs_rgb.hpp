#pragma once
/**
\file       hsl_vs_rgb.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       01.01.2017
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {
/**
  \brief  Функция конвертирует YUY16->HSL
  */
void yuy2_to_hsl_alu (::libs::optim::MCallInfo& _info);
void hsl_to_yuy2_alu (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_alu (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_alu (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_sse1 (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_sse1 (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_sse2 (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_sse2 (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_sse3 (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_sse3 (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_avx1 (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_avx1 (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_avx2 (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_avx2 (::libs::optim::MCallInfo& _info);

void rgb24_to_hsl_neon (::libs::optim::MCallInfo& _info);
void hsl_to_rgb24_neon (::libs::optim::MCallInfo& _info);

}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb
