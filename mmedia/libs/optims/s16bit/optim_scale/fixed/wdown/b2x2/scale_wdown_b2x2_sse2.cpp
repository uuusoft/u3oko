/**
\file       scale_wdown_b2x2_sse2.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "scale_wdown_b2x2.hpp"
#include "scale_wdown_b2x2_int.hpp"

namespace libs::optim::s16bit::scale::fixed::wdown::b2x2
{
#if defined(U3_CPU_X86)
void
sse2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  alu (info);
}
#endif
}   // namespace libs::optim::s16bit::scale::fixed::wdown::b2x2


namespace libs::optim::s16bit::filter::jam
{
#if 0

#  ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2

  void alu_2x2 ( ::libs::optim::io::MCallInfo& info )
  {
    check_aver2x2( info );

    short*      compress8x8       = info.dsts_[0].buf();
    void*     dword_global_average  = info.params_.pints_[0];
    const short*  source          = info.srcs_[0].buf();
    uint32_t* temp_average      = U3_CAST_MEM<uint32_t*>(dword_global_average );

    *temp_average = 0;

    short*      temp_dest   = compress8x8;
    const short*  temp_source   = source;

    for (std::size_t indx_y = 0; indx_y < info.srcs_[0].height_ / 2; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < info.srcs_[0].width_ / 2; ++indx_x )
      {
        const short* base_line_source = U3_CAST_MEM<const short*>( r1einterpret_cast<const unsigned char*>( temp_source )+ indx_y * 2 * info.srcs_[0].stride_ );
        uint32_t base_offset = indx_x * 2;
        short temp_value = (base_line_source[base_offset ] +
          base_line_source[base_offset + 1] +
          U3_CAST_MEM<const short*>( ( U3_CAST_MEM<const unsigned char*>(base_line_source )+ info.srcs_[0].stride_ ) )[base_offset ] +
          U3_CAST_MEM<const short*>( ( U3_CAST_MEM<const unsigned char*>(base_line_source )+ info.srcs_[0].stride_ ) )[base_offset + 1] ) >> 2;

        U3_ASSERT ( temp_value <= 255 );
        U3_ASSERT ( temp_value >= 0);

        temp_dest[indx_x] = temp_value;
        (*temp_average ) += temp_value;
      }

      U3_FAST_MOVE_PTR( temp_dest, info.dsts_[0].stride_ );
    }
    (*temp_average ) /= ( info.srcs_[0].height_ / 2 ) * ( info.srcs_[0].width_ / 2 );
    return;
  }

#  endif

#  ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2

  void alu_deciminate_2x2 ( ::libs::optim::io::MCallInfo& info )
  {
    check( info );

    short*      compress8x8 = info.dsts_[0].buf();
    const short*  source    = info.srcs_[0].buf();

    U3_ASSERT ( compress8x8);
    U3_ASSERT (source );

    short*      temp_dest = compress8x8;
    const short*  temp_source = source;

    for (std::size_t indx_y = 0; indx_y < info.srcs_[0].height_ / 2; ++indx_y)
    {
      for (std::size_t indx_x = 0; indx_x < info.srcs_[0].width_ / 2; ++indx_x )
      {
        const short* base_line_source = U3_CAST_MEM<const short*>( U3_CAST_MEM<const unsigned char*>( temp_source )+ indx_y * 2 * info.srcs_[0].stride_ );
        uint32_t base_offset = indx_x * 2;
        short temp_value = base_line_source[base_offset ];

        U3_ASSERT ( temp_value <= 255 );
        U3_ASSERT ( temp_value >= 0);

        temp_dest[indx_x] = temp_value;
      }

      U3_FAST_MOVE_PTR( temp_dest, info.dsts_[0].stride_ );
    }

    return;
  }

#  endif

#  ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2
  void aver1_2x2_alu (::libs::optim::io::MCallInfo& info )
#  else
  void aver2_2x2_alu (::libs::optim::io::MCallInfo& info )
#  endif
  {
    check_aver2x2( info );
  }

#  if defined(U3_CPU_X86)

#    ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2
  void aver1_2x2_avx1 (::libs::optim::io::MCallInfo& info )
#    else
  void aver2_2x2_avx1 (::libs::optim::io::MCallInfo& info )
#    endif
  {
    check_aver2x2( info );
    U3_ASSERT_SIGNAL( "failed" );
  }

#    ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2
  void aver1_2x2_avx2 (::libs::optim::io::MCallInfo& info )
#    else
  void aver2_2x2_avx2 (::libs::optim::io::MCallInfo& info )
#    endif
  {
    check_aver2x2( info );
    U3_ASSERT_SIGNAL( "failed" );
  }

#    ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2
  void aver1_2x2_sse2 (::libs::optim::io::MCallInfo& info )
#    else
  void aver2_2x2_sse2 (::libs::optim::io::MCallInfo& info )
#    endif
  {
    check_aver2x2( info );

    short*      compress2x2       = info.dsts_[0].buf();
    void*     dword_global_average  = info.params_.pints_[0];
    const short*  source          = info.srcs_[0].buf();

    int number_sub_pixel_x  = info.dsts_[0].width_ / 8;
    int number_sub_pixel_y  = info.dsts_[0].height_ / 2;
    int leak_stride_source  = info.srcs_[0].stride_ - sizeof (short ) * number_sub_pixel_x * 8;
    int leak_stride_dest  = info.dsts_[0].stride_ - sizeof (short ) * number_sub_pixel_x * 4;

    if (number_sub_pixel_x <= 0)
    {
      leak_stride_source -= sizeof (short ) * 8;
      leak_stride_dest -= sizeof (short ) * 2;
    }

    U3_CHECK( ( info.dsts_[0].width_* info.dsts_[0].height_ >= 64 ), "" );

#    ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2  
    unsigned short loc_mask1[8] =
    {
      0xFFFF, 0x0, 0xFFFF, 0x0,
      0xFFFF, 0x0, 0xFFFF, 0x0
    };
#    endif

    const int stride_source  =info.srcs_[0].stride_;

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
    U3_ASSERT_SIGNAL_I64;
    //U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
    __asm
    {
      ; eax - current result for subpixel 2x2;
      ; ebx - cycle for col;
      ; ecx - cycle for row;
      ; edx - source;
      ; edi - stride_source;
      ; esi - compress2x2;
      ; xmm7 - temp result average 2x2;
      ; xmm2 - global average result;

      pushad;

#      ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2  
      lea eax, loc_mask1;
      movdqu xmm3, [eax];
#      endif

      mov ecx, number_sub_pixel_y;
      mov edi, stride_source;
      mov edx, source;
      mov esi, compress2x2;

      pxor xmm2, xmm2;
      pxor xmm5, xmm5;

      cycle_row:

      mov ecx, number_sub_pixel_x;

      //cycle for string;
      cycle_col:

      //for every subpixel 2x2 calculate sub 16x string;
      movdqa xmm7, [edx];
      paddsw xmm7, [edx + edi];
      movdqa xmm6, xmm7;
#      ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2
      psrldq xmm6, 2;
#      else
      psrldq xmm6, 4;
#      endif
      paddsw xmm7, xmm6;
      psraw xmm7, 2;

#      ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2
      pand xmm7, xmm3;
      pshuflw xmm7, xmm7, 88; 00011010;
      pshufhw xmm7, xmm7, 88; 00011010;
      movdqa xmm6, xmm7;
      psrldq xmm6, 4;
      por xmm7, xmm6;
#      endif

      //saved res;
      movdq2q mm0, xmm7;
      movq[esi], mm0;
      add esi, 8;

      //calculate abs global average;
      movq xmm6, xmm7;
      psrldq xmm6, 2;
      paddsw xmm7, xmm6;
      movq xmm6, xmm7;
      psrldq xmm6, 4;
      paddsw xmm7, xmm6;
      psraw xmm7, 2;

      pxor xmm4, xmm4;
      psubusw xmm4, xmm7;
      psubusw xmm7, xmm5;
      por xmm7, xmm4;
      punpcklwd xmm7, xmm5;
      paddd xmm2, xmm7;

      //go to next subpixel in array;
      add edx, 16;

      sub ecx, 1;

      ; 24.05.2016;
      jg cycle_col;

      add edx, leak_stride_source;
      add esi, leak_stride_dest;

      //go to next string subpixel - offset 2 x width_string;
      //add offset 8 string;
      add edx, edi;

      sub number_sub_pixel_y, 1;

      ; 24.05.2016;
      jg cycle_row;

      //flush global average
      mov eax, dword_global_average;
      movd[eax], xmm2;

      popad;
      emms;
    }
#    endif

    const int sum_px = number_sub_pixel_x * ( info.dsts_[0].height_ / 2 );

    *U3_CAST_MEM<unsigned long*>(dword_global_average ) = *U3_CAST_MEM<unsigned long*>(dword_global_average ) / sum_px;

    return;
  }

#    ifndef FUNCT2_COMPRESS8X8_SIGNEDWORD_FUNCT_MMX_SSE_SSE2

  void aver1_8x8_avx1 ( ::libs::optim::io::MCallInfo& info )
  {
    check_aver2x2( info );
    U3_ASSERT_SIGNAL( "failed" );
    return;
  }

  void aver1_8x8_avx2 ( ::libs::optim::io::MCallInfo& info )
  {
    check_aver2x2( info );
    U3_ASSERT_SIGNAL( "failed" );
    return;
  }

  void aver1_8x8_sse2 ( ::libs::optim::io::MCallInfo& info )
  {
    check_aver2x2( info );

    short*      compress8x8       = info.dsts_[0].buf();
    void*     dword_global_average  = info.params_.pints_[0];
    const short*  source          = info.srcs_[0].buf();

    int number_sub_pixel_x  = info.dsts_[0].width_ / 8;
    int number_sub_pixel_y  = info.dsts_[0].height_ / 8;
    int leak_stride_source  = info.srcs_[0].stride_ - sizeof (short ) * number_sub_pixel_x * 8;
    int leak_stride_dest  = info.dsts_[0].stride_ - number_sub_pixel_x * sizeof (short );

    if (number_sub_pixel_x <= 0)
    {
      leak_stride_source -= sizeof (short ) * 8;
      leak_stride_dest -= sizeof (short ) * 1;
    }

    U3_CHECK( ( info.dsts_[0].width_ * info.dsts_[0].height_ >= 64 ), "failed" );


#      define ADD_Y8_SSE2_STRING_1 \
        __asm paddsw xmm7, [edx] __asm add edx, edi


    const int stride_source  =info.srcs_[0].stride_;

#      if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
    U3_ASSERT_SIGNAL_I64;
    //U1UU_THROW_EXCEPTION("req intrinsic impl") );
#      else
    __asm
    {
      ; eax - current result for subpixel 8x8;
      ; ebx - cycle for col;
      ; ecx - cycle for row;
      ; edx - source;
      ; edi - stride_source;
      ; esi - compress8x8;
      ; xmm7 - temp result average 8x8;
      ; xmm6 - global average result;

      pushad;

      //init value;
      mov ecx, number_sub_pixel_y;
      mov edi, stride_source;
      mov edx, source;
      mov esi, compress8x8;

      pxor xmm6, xmm6;
      pxor xmm4, xmm4;

      cycle_row:

      mov ecx, number_sub_pixel_x;

      //cycle for string
      cycle_col:

      //cycle for subpixel 8x8   
      pxor xmm7, xmm7;

      //for every subpixel 8x8 calculate sub 8x string
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;
      ADD_Y8_SSE2_STRING_1;

      movdqa xmm5, xmm7;
      psrldq xmm5, 8;
      paddsw xmm7, xmm5;
      movdqa xmm5, xmm7;
      psrldq xmm5, 4;
      paddsw xmm7, xmm5;
      movdqa xmm5, xmm7;
      psrldq xmm5, 2;
      paddsw xmm7, xmm5;
      psraw xmm7, 6;
      movd eax, xmm7;

      //calculate abs global average
      pxor xmm4, xmm4;
      pxor xmm5, xmm5;
      psubusw xmm4, xmm7;
      psubusw xmm7, xmm5;
      por xmm7, xmm4;
      punpcklwd xmm7, xmm5;
      paddd xmm6, xmm7;

      //flush average value in output array;
      mov word ptr[esi], ax;
      add esi, 2;

      //go to next subpixel in array;
      shl edi, 3;
      sub edx, edi;
      shr edi, 3;

      add edx, 16;

      sub ecx, 1;

      ; 24.05.2016;
      jg cycle_col;

      add edx, leak_stride_source;
      add esi, leak_stride_dest;

      //go to next string subpixel - offset 8 x width_string;
      //add offset 8 string;
      sub edx, edi;
      shl edi, 3;
      add edx, edi;
      shr edi, 3;

      sub number_sub_pixel_y, 1;

      ; 24.05.2016;
      jg cycle_row;

      //flush global average
      mov eax, dword_global_average;
      movd[eax], xmm6;

      popad;
      emms;
    }
#      endif

    *U3_CAST_MEM<unsigned long*>(dword_global_average ) = (*U3_CAST_MEM<unsigned long*>(dword_global_average ) ) / (number_sub_pixel_x * ( info.dsts_[0].height_ / 8) );

#      undef ADD_Y8_SSE2_STRING_1

    return;
  }
#    endif
#  endif
#endif
}   // namespace libs::optim::s16bit::filter::jam
