/**
\file       matrix1_sse2.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "matrix1.hpp"

#if defined(U3_CPU_X86)

// old shit
namespace libs::optim::s16bit::gen::matrix1
{
bool
matrix_sse2 (::libs::optim::io::MCallInfo& info)
{
#  if 0
  U3_ASSERT (info.check ());
  base_funcs::c1heck_bound< std::int16_t > (info.params_.ints_[1], 0, 255);

  const std::int16_t loc_array_koeff_assemble_blocks[8] = {
    info.params_.ints_[1], info.params_.ints_[1], info.koeff_assemble_blocks_, info.koeff_assemble_blocks_, info.koeff_assemble_blocks_, info.koeff_assemble_blocks_, info.koeff_assemble_blocks_, info.koeff_assemble_blocks_
  };
#    define SIZE_BLOCK_MATRIX_EFFECT (8)

  std::uint32_t loc_number_blocks_x = info.width_element_ / SIZE_BLOCK_MATRIX_EFFECT;
  std::uint32_t loc_number_blocks_y = info.height_element_ / SIZE_BLOCK_MATRIX_EFFECT;

  std::uint32_t loc_selected_index_block           = 0;
  std::uint16_t loc_current_min_diff_between_block = 0;

  std::uint32_t counter_cycle1 = loc_number_blocks_y;
  std::uint32_t counter_cycle2 = loc_number_blocks_x;

  std::uint32_t counter_number_blocks = 0;

  int add_leak_source_string = info.stride_source_ - loc_number_blocks_x * SIZE_BLOCK_MATRIX_EFFECT * sizeof (std::int16_t);

  std::int16_t loc_flag_update_ext_buf = (info.params_.parrayss_[1] && (info.dsts_.size () > 1 ? info.dsts_[1].buf () : 0)) ? 1 : 0;

  const void*    source                                    = info.dsts_[0].buf ();
  const void*    ext_source2                               = info.dsts_.size () > 1 ? info.dsts_[1].buf () : 0;
  std::int16_t   bound_koeff_block                         = info.params_.ints_[2];
  int            stride_source                             = info.stride_source_;
  std::int16_t** array_blocks_8x8                          = info.params_.parrayss_[0];
  std::int16_t** array_blocks_8x8_for_ext_source2          = info.params_.parrayss_[1];
  std::int16_t** extended_array_blocks_8x8                 = info.params_.parrayss_[2];
  std::int16_t** extended_array_blocks_8x8_for_ext_source2 = info.params_.parrayss_[3];
  std::uint32_t  number_blocks                             = info.params_.ints_[0];

    __asm
    {
      ; eax ebx ecx edx edi esi;
      pushad;

      ; eax - временной регистр;
      ; edi - начало текущего блоко в переданном массиве, который будет виде пользователю;
      ; edx - шаг в переданном массиве;
      ; ebx - временной регистр;
      ; esi - начало текущего блоко во втором переданном массиве, который будет виде пользователю;
      mov edi, source;
      ; 07.02.2016;
      mov esi, ext_source2;
      mov edx, stride_source;

      lea eax, loc_array_koeff_assemble_blocks;
      movdqu xmm6, [eax];

      cycle1:

      mov eax, loc_number_blocks_x;
      mov counter_cycle2, eax;

      cycle2:

      mov eax, number_blocks;
      mov counter_number_blocks, eax;
      mov loc_current_min_diff_between_block, 0x7FFF;

      cycle3:
      sub counter_number_blocks, 1;
      mov ebx, counter_number_blocks;
      shl ebx, 2;
      add ebx, array_blocks_8x8;
      mov eax, [ebx];

      ; вычисления разности между текущим блоком в исходном изображении и текущим блоком в списке;
      ; обнуляем регистр в котором будет хранится сумма обсолютных разностей;
      pxor xmm7, xmm7;

      mov ebx, edi;

#    define GET_ABS_DIFF_FROM_STRING_SSE2(offset2) \
      __asm movdqa xmm0, [ebx] __asm movdqa xmm2, [eax + offset2] __asm movdqa xmm4, xmm0 __asm psubusw xmm4, xmm2 __asm psubusw xmm2, xmm0 __asm por xmm2, xmm4 __asm paddusw xmm7, xmm2 __asm add ebx, edx;

      GET_ABS_DIFF_FROM_STRING_SSE2 (0 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (1 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (2 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 ( 3 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (4 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (5 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 ( 6 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (7 * 16);

#    ifdef CALCULATE_DIFF_BETWEEN_COLOR_AND_SECOND_STREAM
      mov ax, loc_flag_update_ext_buf;
      cmp ax, 1;
      jl skip_calculate_diff_color_block;

      mov ebx, counter_number_blocks;
      shl ebx, 2;
      add ebx, array_blocks_8x8_for_ext_source2;
      mov eax, [ebx];
      mov ebx, esi;

      GET_ABS_DIFF_FROM_STRING_SSE2 (0 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (1 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (2 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 ( 3 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (4 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (5 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 ( 6 * 16);
      GET_ABS_DIFF_FROM_STRING_SSE2 (7 * 16);

      skip_calculate_diff_color_block:
#    endif


#    undef GET_ABS_DIFF_FROM_STRING_SSE2

      ; производим окончательный подсчет суммы (8 числа) обсолтной разности в регистре и фиксируем это;
      ; если данная разность минимальна фиксируем индекс блока в списке сравнениваемых блоков;
      ; чтобы потом работать с блоком с наименьшей разностью от текущего;
      ; ready for SSE2 opt;
      movdqa xmm5, xmm7;
      psrldq xmm5, 8;
      paddusw xmm7, xmm5;
      movdqa xmm5, xmm7;
      psrldq xmm5, 4;
      paddusw xmm7, xmm5;
      movdqa xmm5, xmm7;
      psrldq xmm5, 2;
      paddusw xmm7, xmm5;
      ; 10.02.2016
#    if 0
#      ifdef CALCULATE_DIFF_BETWEEN_COLOR_AND_SECOND_STREAM
        psraw xmm7, 7;
#      else
        psraw xmm7, 6;
#      endif
#    endif
      ; производим сброс полученного резальтата в память, если данный результат наименьший фиксируем его и индекс блока;
      movd eax, xmm7;
      cmp ax, loc_current_min_diff_between_block;
      jg skip_set_min_value;

      mov loc_current_min_diff_between_block, ax;
      mov eax, counter_number_blocks;
      mov loc_selected_index_block, eax;

      skip_set_min_value:

      cmp counter_number_blocks, 0;
      jg cycle3;


      xor eax, eax;
      mov ax, loc_current_min_diff_between_block;

#    ifdef CALCULATE_DIFF_BETWEEN_COLOR_AND_SECOND_STREAM
      shr ax, 7;
#    else
      shr ax, 6;
#    endif

      mov bx, bound_koeff_block;
      cmp bx, ax;
      jl skip_update_block;

      ; замещение со слиянием выбранного блока и текущего блока в исходном изображении;
      ; 06.02.2016 вычисляем текущий коэффициент сложения для данного блока на основе глобального коэффиента и коэффициента уникального для данного блока;
      ; 07.02.2016;
      ; ready for SSE2opt;
      movd xmm0, eax;
      pshuflw xmm0, xmm0, 0;
      pshufd xmm0, xmm0, 0;

      pcmpeqw xmm4, xmm4; mm4 = 0xffffffffffffffff;
      psrlw xmm4, 8; mm4 = 0x00ff00ff00ff00ff00ff;
      psubusw xmm4, xmm0;

      pmullw xmm4, xmm6;
      psrlw xmm4, 5;

      packuswb xmm4, xmm4;
      pxor xmm1, xmm1;
      punpcklbw xmm4, xmm1;
      movdqa xmm3, xmm4;

      pcmpeqw xmm4, xmm4; mm4 = 0xffffffffffffffff;
      psrlw xmm4, 8; mm4 = 0x00ff00ff00ff00ff00ff;
      psubusw xmm4, xmm3;

      mov ebx, loc_selected_index_block;
      shl ebx, 2;
      ; 11.02.2016;
      add ebx, extended_array_blocks_8x8;
      mov eax, [ebx];

      cmp eax, 0;
      jle skip_update_first_block;

      pxor xmm7, xmm7;
      mov ebx, edi;

#    define ADD_STRINGS_SOURCE_AND_DEST_SSE2(offset2) \
      __asm movdqa xmm0, [ebx] __asm pmullw xmm0, xmm4 __asm psrlw xmm0, 8 __asm movdqa xmm2, [eax + offset2] __asm pmullw xmm2, xmm3 __asm psrlw xmm2, 8 __asm paddusw xmm0, xmm2 __asm movdqa[ebx], xmm0 __asm add ebx, edx;

      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (0 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (1 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (2 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 ( 3 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (4 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (5 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 ( 6 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (7 * 16);

      skip_update_first_block:

      ; 07.02.2016 проверяем флаг требования обнволения второго блока;
      ; если требуется производим обновление второго массива через второй список блоков;
      ; используя найденный индекс из первого списка, т.е.списки должны быть идентичной длины;
      mov ax, loc_flag_update_ext_buf;
      cmp ax, 1;
      jl skip_update_block;

      mov ebx, loc_selected_index_block;
      shl ebx, 2;
      add ebx, extended_array_blocks_8x8_for_ext_source2;
      mov eax, [ebx];
      cmp eax, 0;
      jle skip_update_second_block;

      pxor xmm7, xmm7;
      mov ebx, esi;

      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (0 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (1 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (2 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 ( 3 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (4 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (5 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 ( 6 * 16);
      ADD_STRINGS_SOURCE_AND_DEST_SSE2 (7 * 16);

#    undef ADD_STRINGS_SOURCE_AND_DEST_SSE2

  skip_update_second_block :
  skip_update_block :

      ; end cycle 2;

      add edi, 16;
      ; 07.02.2016;
      add esi, 16;
      sub counter_cycle2, 1;
      jg cycle2;

      ; end cycle 1;
      add edi, add_leak_source_string;
      add edi, edx;
      add edi, edx;
      add edi, edx;
      add edi, edx;
      add edi, edx;
      add edi, edx;
      add edi, edx;

      add esi, add_leak_source_string;
      add esi, edx;
      add esi, edx;
      add esi, edx;
      add esi, edx;
      add esi, edx;
      add esi, edx;
      add esi, edx;

      sub counter_cycle1, 1;
      jg cycle1;

      popad;
      emms;
    }
#  endif
  return true;
}
}   // namespace libs::optim::s16bit::gen::matrix1


#endif
