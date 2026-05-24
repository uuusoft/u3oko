/**
\file       base_3x3_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_optim_conv
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "base_3x3.hpp"

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::base::c3x3
{
void
mod_sse2 (::libs::optim::io::MCallInfo& info)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  const cores::values_core_type* mask      = 0;
  std::int16_t                   mul_koeff = 0;

  TTParams< cores::values_core_type > ().get_params (info, mask, mul_koeff);

  std::int16_t mul_koeffs[8]  = { mul_koeff, 0, 0, 0, 0, 0, mul_koeff, 0 };
  std::int16_t mask_koeff1[8] = { (*mask).get (0, 0), (*mask).get (1, 0), (*mask).get (2, 0), 0, (*mask).get (0, 0), (*mask).get (1, 0), (*mask).get (2, 0), 0 };
  std::int16_t mask_koeff2[8] = { (*mask).get (0, 1), (*mask).get (1, 1), (*mask).get (2, 1), 0, (*mask).get (0, 1), (*mask).get (1, 1), (*mask).get (2, 1), 0 };
  std::int16_t mask_koeff3[8] = { (*mask).get (0, 2), (*mask).get (1, 2), (*mask).get (2, 2), 0, (*mask).get (0, 2), (*mask).get (1, 2), (*mask).get (2, 2), 0 };

  U3_ASSERT (std::size (mask_koeff1) == std::size (mask_koeff2));
  U3_ASSERT (std::size (mask_koeff1) == std::size (mask_koeff3));

  std::uint32_t width           = info.srcs_[0].width_;    // - 2 * consts::short_from_edge;
  std::uint32_t height          = info.srcs_[0].height_;   // - 2 * consts::strings_from_edge;
  std::uint32_t count_str_bytes = ((((width & 0x7) ? width + 8 : width) >> 3) << 3) * sizeof (std::int16_t);
  std::uint32_t bytes_leak      = info.srcs_[0].stride_ - count_str_bytes;

  const std::int16_t* sbuf   = info.srcs_[0].buf ();
  std::int16_t*       dbuf   = info.dsts_[0].buf ();
  std::uint32_t       stride = info.srcs_[0].stride_;

  __asm {
#    define REG_SOURCE_BUFFER esi
#    define REG_DESTINATION_BUFFER edi
#    define REG_CYCLE_PIXEL_STRING ecx
#    define REG_CYCLE_STRINGS ebx
#    define REG_STRIDE_BUFFERS eax
#    define REG_LEAKE_STRIDE_BUFFERS edx
#    define REG_TEMP1 edx

#    define SSEREG_KOEFF_MULL_RES xmm2

#    define SSEREG_TEMP1 xmm0
#    define SSEREG_TEMP2 xmm1
#    define SSEREG_TEMP4 xmm7

#    define SSEREG_STRING1_MASK xmm4
#    define SSEREG_STRING2_MASK xmm5
#    define SSEREG_STRING3_MASK xmm6

      pushad;

      ; загружаем коэффициенты для иммитации деления результата;
      movdqu SSEREG_KOEFF_MULL_RES, mul_koeffs;

      ; загружаем коэффициенты маски длс свертки;
      movdqu SSEREG_STRING1_MASK, mask_koeff1;
      movdqu SSEREG_STRING2_MASK, mask_koeff2;
      movdqu SSEREG_STRING3_MASK, mask_koeff3;

      ; инициализируем изменяемые переменные;
      mov REG_DESTINATION_BUFFER, dbuf;
      mov REG_SOURCE_BUFFER, sbuf;
      mov REG_STRIDE_BUFFERS, stride;
      mov REG_CYCLE_STRINGS, height;

      ; цикл по строкам;
      cycle1:
      ; инциализируем переменные для внутреннего цикла по строке;
      mov REG_CYCLE_PIXEL_STRING, width;

      ; цикл по стобцам строки;
      cycle2:
      ; макрос для вычисления свертки одного пикселя - слова;
      ; загружаем исходные данные окрестности 3x3 пикселя три строки по 4 слова;
      ; вычисляем свертку с маской;

      ; вычисляем сверутку для 8 пикселей - слов, чтобы сформировать полный MMX регистр;
      pxor SSEREG_TEMP4, SSEREG_TEMP4;

#    define SSE_ONE_PIXEL_STRING                                                                                                                                                                                                                                                                               \
      /*загружаем данные из источника и сразу вычисляем свертку*/                                                                                                                                                                                                                                              \
      __asm sub REG_SOURCE_BUFFER, REG_STRIDE_BUFFERS __asm movdqu SSEREG_TEMP1, [REG_SOURCE_BUFFER - 2] /*копируем младшую половину в старшую, нам фактчески инетерсны первые 4 слова*/                                                                                                                       \
        __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP1, 68 /*перемещаем слова в старшей половиние убираю ненужные слова*/                                                                                                                                                                                                                        \
        __asm pshufhw SSEREG_TEMP1,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP1, 57 __asm add REG_SOURCE_BUFFER, REG_STRIDE_BUFFERS __asm pmaddwd SSEREG_TEMP1, SSEREG_STRING1_MASK __asm movdqu SSEREG_TEMP2, [REG_SOURCE_BUFFER - 2] /*копируем младшую половину в старшую, нам фактчески инетерсны первые 4 слова*/                                                    \
        __asm pshufd SSEREG_TEMP2,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP2, 68 /*перемещаем слова в старшей половиние убираю ненужные слова*/                                                                                                                                                                                                                        \
        __asm pshufhw SSEREG_TEMP2,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP2, 57 __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING2_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqu SSEREG_TEMP2, [REG_SOURCE_BUFFER + REG_STRIDE_BUFFERS - 2] /*копируем младшую половину в старшую, нам фактчески инетерсны первые 4 слова*/                                        \
        __asm pshufd SSEREG_TEMP2,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP2, 68 /*перемещаем слова в старшей половиние убираю ненужные слова*/                                                                                                                                                                                                                        \
        __asm pshufhw SSEREG_TEMP2,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP2, 57 __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING3_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqa SSEREG_TEMP2, SSEREG_TEMP1 __asm psrldq SSEREG_TEMP2, 4 __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 /* 11.05.2016 дмоножаем результат на коэффициент и иммтируем деление через сдвиг*/ \
        __asm packssdw             SSEREG_TEMP1,                                                                                                                                                                                                                                                               \
        SSEREG_TEMP1 __asm pmaddwd SSEREG_TEMP1, SSEREG_KOEFF_MULL_RES __asm psrad SSEREG_TEMP1, U3_SHIFT_MUL_KOEFF_CONVOLUTION /*ограничиваем результат*/                                                                                                                                                     \
        __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP1, 12 __asm packssdw SSEREG_TEMP1, SSEREG_TEMP1 /*фиксируем во временном регистре*/                                                                                                                                                                                                         \
        __asm psrldq   SSEREG_TEMP4,                                                                                                                                                                                                                                                                           \
        4 __asm pslldq SSEREG_TEMP1, 12 __asm por SSEREG_TEMP4, SSEREG_TEMP1 /*перемещаемся на следущие два пикселя-слово в источнике*/                                                                                                                                                                        \
        __asm add REG_SOURCE_BUFFER,                                                                                                                                                                                                                                                                           \
        4

      SSE_ONE_PIXEL_STRING;
      SSE_ONE_PIXEL_STRING;
      SSE_ONE_PIXEL_STRING;
      SSE_ONE_PIXEL_STRING;

      ; на данный момент вычисленно 8 пикселя - слова;
      ; вычисляем модуль результата;

      pxor SSEREG_TEMP1, SSEREG_TEMP1;
      pxor SSEREG_TEMP2, SSEREG_TEMP2;
      psubusw SSEREG_TEMP2, SSEREG_TEMP4;
      psubusw SSEREG_TEMP4, SSEREG_TEMP1;
      por SSEREG_TEMP4, SSEREG_TEMP2;


      ; 11.05.2016 расширил до двойного слова;
      ; фиксируем резальтат в памяти;
      movdqa[REG_DESTINATION_BUFFER], SSEREG_TEMP4;

      ; смещаемся на следущие 8 пиксель - слово;
      add REG_DESTINATION_BUFFER, 16;

      sub REG_CYCLE_PIXEL_STRING, 8;
      jg cycle2;

      mov REG_LEAKE_STRIDE_BUFFERS, bytes_leak;

      add REG_SOURCE_BUFFER, REG_LEAKE_STRIDE_BUFFERS;
      add REG_DESTINATION_BUFFER, REG_LEAKE_STRIDE_BUFFERS;

      sub REG_CYCLE_STRINGS, 1;
      jg cycle1;

      popad;
      emms;

#    undef SSE_ONE_PIXEL_STRING

#    undef REG_SOURCE_BUFFER
#    undef REG_DESTINATION_BUFFER
#    undef REG_CYCLE_PIXEL_STRING
#    undef REG_CYCLE_STRINGS
#    undef REG_STRIDE_BUFFERS
#    undef REG_LEAKE_STRIDE_BUFFERS
#    undef REG_TEMP1

#    undef SSEREG_KOEFF_MULL_RES
#    undef SSEREG_TEMP1
#    undef SSEREG_TEMP2

#    undef SSEREG_STRING1_MASK
#    undef SSEREG_STRING2_MASK
#    undef SSEREG_STRING3_MASK
  }
#  endif
  return;
}

void
sse2 (::libs::optim::io::MCallInfo& info)
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  const cores::values_core_type* mask      = 0;
  std::int16_t                   mul_koeff = 0;

  TTParams< cores::values_core_type > ().get_params (info, mask, mul_koeff);

  std::int16_t mul_koeffs[8]  = { mul_koeff, 0, 0, 0, 0, 0, mul_koeff, 0 };
  std::int16_t mask_koeff1[8] = { (*mask).get (0, 0), (*mask).get (1, 0), (*mask).get (2, 0), 0, (*mask).get (0, 0), (*mask).get (1, 0), (*mask).get (2, 0), 0 };
  std::int16_t mask_koeff2[8] = { (*mask).get (0, 1), (*mask).get (1, 1), (*mask).get (2, 1), 0, (*mask).get (0, 1), (*mask).get (1, 1), (*mask).get (2, 1), 0 };
  std::int16_t mask_koeff3[8] = { (*mask).get (0, 2), (*mask).get (1, 2), (*mask).get (2, 2), 0, (*mask).get (0, 2), (*mask).get (1, 2), (*mask).get (2, 2), 0 };
  // std::int16_t mask_koeff1[8] = {(*mask)[0], (*mask)[1], (*mask)[2], 0, (*mask)[0], (*mask)[1], (*mask)[2], 0};
  // std::int16_t mask_koeff2[8] = {(*mask)[3], (*mask)[4], (*mask)[5], 0, (*mask)[3], (*mask)[4], (*mask)[5], 0};
  // std::int16_t mask_koeff3[8] = {(*mask)[6], (*mask)[7], (*mask)[8], 0, (*mask)[6], (*mask)[7], (*mask)[8], 0};

  U3_ASSERT (std::size (mask_koeff1) == std::size (mask_koeff2));
  U3_ASSERT (std::size (mask_koeff1) == std::size (mask_koeff3));

  std::uint32_t width           = info.srcs_[0].width_;    // - 2 * consts::short_from_edge;
  std::uint32_t height          = info.srcs_[0].height_;   // - 2 * consts::strings_from_edge;
  std::uint32_t count_str_bytes = ((((width & 0x7) ? width + 8 : width) >> 3) << 3) * sizeof (std::int16_t);
  std::uint32_t bytes_leak      = info.srcs_[0].stride_ - count_str_bytes;

  const std::int16_t* sbuf   = info.srcs_[0].buf ();
  std::int16_t*       dbuf   = info.dsts_[0].buf ();
  std::uint32_t       stride = info.srcs_[0].stride_;

  __asm {
#    define REG_SOURCE_BUFFER esi
#    define REG_DESTINATION_BUFFER edi
#    define REG_CYCLE_PIXEL_STRING ecx
#    define REG_CYCLE_STRINGS ebx
#    define REG_STRIDE_BUFFERS eax
#    define REG_LEAKE_STRIDE_BUFFERS edx
#    define REG_TEMP1 edx

#    define SSEREG_KOEFF_MULL_RES xmm2

#    define SSEREG_TEMP1 xmm0
#    define SSEREG_TEMP2 xmm1
#    define SSEREG_TEMP4 xmm7

#    define SSEREG_STRING1_MASK xmm4
#    define SSEREG_STRING2_MASK xmm5
#    define SSEREG_STRING3_MASK xmm6

      pushad;

      ; загружаем коэффициенты для иммитации деления результата;
      movdqu SSEREG_KOEFF_MULL_RES, mul_koeffs;

      ; загружаем коэффициенты маски длс свертки;
      movdqu SSEREG_STRING1_MASK, mask_koeff1;
      movdqu SSEREG_STRING2_MASK, mask_koeff2;
      movdqu SSEREG_STRING3_MASK, mask_koeff3;

      ; инициализируем изменяемые переменные;
      mov REG_DESTINATION_BUFFER, dbuf;
      mov REG_SOURCE_BUFFER, sbuf;
      mov REG_STRIDE_BUFFERS, stride;
      mov REG_CYCLE_STRINGS, height;

      ; цикл по строкам;
      cycle1:
      ; инциализируем переменные для внутреннего цикла по строке;
      mov REG_CYCLE_PIXEL_STRING, width;

      ; цикл по стобцам строки;
      cycle2:
      ; макрос для вычисления свертки одного пикселя - слова;
      ; загружаем исходные данные окрестности 3x3 пикселя три строки по 4 слова;
      ; вычисляем свертку с маской;

      ; вычисляем сверутку для 8 пикселей - слов, чтобы сформировать полный MMX регистр;
      pxor SSEREG_TEMP4, SSEREG_TEMP4;

#    define SSE_ONE_PIXEL_STRING                                                                                                                                                                                                                                                                               \
      /*загружаем данные из источника и сразу вычисляем свертку*/                                                                                                                                                                                                                                              \
      __asm sub REG_SOURCE_BUFFER, REG_STRIDE_BUFFERS __asm movdqu SSEREG_TEMP1, [REG_SOURCE_BUFFER - 2] /*копируем младшую половину в старшую, нам фактчески инетерсны первые 4 слова*/                                                                                                                       \
        __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP1, 68 /*перемещаем слова в старшей половиние убираю ненужные слова*/                                                                                                                                                                                                                        \
        __asm pshufhw SSEREG_TEMP1,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP1, 57 __asm add REG_SOURCE_BUFFER, REG_STRIDE_BUFFERS __asm pmaddwd SSEREG_TEMP1, SSEREG_STRING1_MASK __asm movdqu SSEREG_TEMP2, [REG_SOURCE_BUFFER - 2] /*копируем младшую половину в старшую, нам фактчески инетерсны первые 4 слова*/                                                    \
        __asm pshufd SSEREG_TEMP2,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP2, 68 /*перемещаем слова в старшей половиние убираю ненужные слова*/                                                                                                                                                                                                                        \
        __asm pshufhw SSEREG_TEMP2,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP2, 57 __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING2_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqu SSEREG_TEMP2, [REG_SOURCE_BUFFER + REG_STRIDE_BUFFERS - 2] /*копируем младшую половину в старшую, нам фактчески инетерсны первые 4 слова*/                                        \
        __asm pshufd SSEREG_TEMP2,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP2, 68 /*перемещаем слова в старшей половиние убираю ненужные слова*/                                                                                                                                                                                                                        \
        __asm pshufhw SSEREG_TEMP2,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP2, 57 __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING3_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqa SSEREG_TEMP2, SSEREG_TEMP1 __asm psrldq SSEREG_TEMP2, 4 __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 /* 11.05.2016 дмоножаем результат на коэффициент и иммтируем деление через сдвиг*/ \
        __asm packssdw             SSEREG_TEMP1,                                                                                                                                                                                                                                                               \
        SSEREG_TEMP1 __asm pmaddwd SSEREG_TEMP1, SSEREG_KOEFF_MULL_RES __asm psrad SSEREG_TEMP1, U3_SHIFT_MUL_KOEFF_CONVOLUTION /*ограничиваем результат*/                                                                                                                                                     \
        __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                             \
        SSEREG_TEMP1, 12 __asm packssdw SSEREG_TEMP1, SSEREG_TEMP1 /*фиксируем во временном регистре*/                                                                                                                                                                                                         \
        __asm psrldq   SSEREG_TEMP4,                                                                                                                                                                                                                                                                           \
        4 __asm pslldq SSEREG_TEMP1, 12 __asm por SSEREG_TEMP4, SSEREG_TEMP1 /*перемещаемся на следущие два пикселя-слово в источнике*/                                                                                                                                                                        \
        __asm add REG_SOURCE_BUFFER,                                                                                                                                                                                                                                                                           \
        4

      SSE_ONE_PIXEL_STRING;
      SSE_ONE_PIXEL_STRING;
      SSE_ONE_PIXEL_STRING;
      SSE_ONE_PIXEL_STRING;

      ; на данный момент вычисленно 8 пикселя - слова;
      ; 11.05.2016 расширил до двойного слова;
      ; фиксируем резальтат в памяти;
      movdqa[REG_DESTINATION_BUFFER], SSEREG_TEMP4;

      ; смещаемся на следущие 8 пиксель - слово;
      add REG_DESTINATION_BUFFER, 16;

      sub REG_CYCLE_PIXEL_STRING, 8;
      jg cycle2;

      mov REG_LEAKE_STRIDE_BUFFERS, bytes_leak;

      add REG_SOURCE_BUFFER, REG_LEAKE_STRIDE_BUFFERS;
      add REG_DESTINATION_BUFFER, REG_LEAKE_STRIDE_BUFFERS;

      sub REG_CYCLE_STRINGS, 1;
      jg cycle1;

      popad;
      emms;

#    undef SSE_ONE_PIXEL_STRING

#    undef REG_SOURCE_BUFFER
#    undef REG_DESTINATION_BUFFER
#    undef REG_CYCLE_PIXEL_STRING
#    undef REG_CYCLE_STRINGS
#    undef REG_STRIDE_BUFFERS
#    undef REG_LEAKE_STRIDE_BUFFERS
#    undef REG_TEMP1

#    undef SSEREG_KOEFF_MULL_RES
#    undef SSEREG_TEMP1
#    undef SSEREG_TEMP2

#    undef SSEREG_STRING1_MASK
#    undef SSEREG_STRING2_MASK
#    undef SSEREG_STRING3_MASK
  }
#  endif
}

}   // namespace libs::optim::s16bit::conv::base::c3x3

#endif
