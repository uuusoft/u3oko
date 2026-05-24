/**
\file       scale_nearest_sse2.cpp
\date       01.11.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru

\project    u3_optim_libs_scale
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "scale_nearest.hpp"
#include "scale_nearest_int.hpp"

namespace libs::optim::s16bit::scale::flow::wany::nearest
{
#if defined(U3_CPU_X86)
U3_SET_TARGET_CPU (avx)
void
sse2 (::libs::optim::io::MCallInfo& info)
{
  alu (info);
}
#endif
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest


// old shit
namespace libs::optim::s16bit::scale::flow::wany::nearest
{
#if 0
#  if defined(U3_CPU_X86)
  struct TImplScale1_SSE2
  {

    void operator()(
      const ::libs::optim::io::ProxyBuf& src,
      ::libs::optim::io::ProxyBuf&       dst,
      int*                                stride_output,
      int*                                max_out_size,
      const bool                          fill_leak )
    {
      //alloc temporal buf for store index
      //temp_string_index.alloc ( dst.height_ );

      int align_width = base_funcs::mem::get_align8( dst.width_ );

      U3_CHECK( ( (sizeof (short ) * align_width * dst.height_ <= *max_out_size ) ),        "");

      //temp_pixel_index.alloc ( align_width);
      ::libs::helpers::mem::IBlockMem::ptr temp_string_index = ::libs::iproperties::helpers::cast_prop_demons()->get_mem_lockfree()->alloc( dst.height_ * sizeof(unsigned long) );
      ::libs::helpers::mem::IBlockMem::ptr temp_pixel_index = ::libs::iproperties::helpers::cast_prop_demons()->get_mem_lockfree()->alloc( align_width * sizeof(unsigned long) );

      U3_CHECK( ( (0 != temp_string_index.get () ) && (0 != temp_pixel_index.get () ) ), "failed");
      U3_ASSERT_SIGNAL( "failed" );
      //temp_pixel_index.fill (0);

      if (0 == *stride_output )
      {
        *stride_output = ::libs::helpers::mem::get_align32( align_width * sizeof( short ) );
      }

      int leak_width_output = *stride_output - align_width * sizeof (short );

      U3_CHECK( ( (*stride_output ) * dst.height_ <= *max_out_size ), "failed" );

      init_indxs_scaler (
        temp_string_index, temp_pixel_index,
        src.width_, src.height_,
        dst.width_, dst.height_,
        src.stride_, src.buf() );

      unsigned long* temp_temp_string_index = temp_string_index->get_as<unsigned long>();
      unsigned long* temp_temp_pixel_index = temp_pixel_index->get_as<unsigned long>();

      short*  output     = dst.buf();
      int   height_output  = dst.height_;

#    if defined(U1UU_CPU_X86_64) || defined(U3_OS_ANDROID)
    U1ASSERT_SIGNAL_I64;
    //U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
      __asm
      {
        pushad;

        ; init reg;
        mov ecx, height_output;
        mov ebx, temp_temp_string_index;
        mov edi, output;

cycle1:
        ; load offset in input current string and repliacate value;
        movd xmm7, [ebx];
        pshufd xmm7, xmm7, 0;

        push ebx;

        ; update temporarely reg;
        mov ebx, temp_temp_pixel_index;
        mov eax, align_width;//width_output;

cycle2:
        //complite first 4 pixel
        movdqa xmm4, [ebx];
        paddd xmm4, xmm7;

        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 0;

        psrldq xmm4, 4;
        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 1;

        psrldq xmm4, 4;
        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 2;

        psrldq xmm4, 4;
        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 3;

        //complite last 4 pixel
        movdqa xmm4, [ebx + 16];
        paddd xmm4, xmm7;

        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 4;

        psrldq xmm4, 4;
        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 5;

        psrldq xmm4, 4;
        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 6;

        psrldq xmm4, 4;
        xor edx, edx;
        movd esi, xmm4;
        pinsrw xmm2, [esi], 7;

        //saved 8 pixel in output
        movdqa[edi], xmm2;

        add edi, 16;
        add ebx, 32;
        sub eax, 8;
        jg cycle2;

        ; offset from index begin string;
        pop ebx;
        add ebx, 4;

        ; 25.09.2016;
        ; add leak in output array;
        add edi, leak_width_output;

        sub ecx, 1;
        jg cycle1;

        popad;
        emms;
      }
#    endif
      return;
    }
  };

  void sse2 ( ::libs::optim::io::MCallInfo& info )
  {
    return nearest_scale< TImplScale1_SSE2 >( info );
  }
#  endif
#endif
}   // namespace libs::optim::s16bit::scale::flow::wany::nearest
