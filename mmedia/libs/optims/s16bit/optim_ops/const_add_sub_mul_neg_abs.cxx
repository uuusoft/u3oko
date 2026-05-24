/**
\file       const_add_sub_mul_neg_abs.cxx
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/
#include "const_add_sub_mul_neg_abs.hpp"

namespace libs::optim::s16bit::ops
{
#ifndef U3_CHECK_FAST_ARGS_OPTIM_FUNCTS
#  ifndef ALLREADEY_OUTPUT_U3_CHECK_FAST_ARGS_OPTIM_FUNCTS
#    define ALLREADEY_OUTPUT_U3_CHECK_FAST_ARGS_OPTIM_FUNCTS
#  endif

#  ifdef SET_UNALIGNED_FUNCT
#    define CHECK_ARG2(mask_dest)
#  else
#    define CHECK_ARG2(mask_dest)                                                                                       \
      if ((U3_CAST_REINTERPRET< long long > (info.dsts_[0].buf ()) & mask_dest) || (info.dsts_[0].stride_ & mask_dest)) \
      {                                                                                                                 \
        U3_ASSERT_SIGNAL ("failed");                                                                                    \
        return;                                                                                                         \
      }

#    define CHECK_ARG2_FOR_SATURATION(mask_dest)                                                                        \
      if ((U3_CAST_REINTERPRET< long long > (info.dsts_[0].buf ()) & mask_dest) || (info.dsts_[0].stride_ & mask_dest)) \
      {                                                                                                                 \
        U3_ASSERT_SIGNAL ("failed");                                                                                    \
        return;                                                                                                         \
      }

#  endif
#else
#  define CHECK_ARG2(mask_dest)
#  define CHECK_ARG2_FOR_SATURATION(mask_dest)
#endif


#ifndef SET_UNMASKDEST_FUNCT
#  ifndef SET_UNALIGNED_FUNCT


void
sat_2byte_alu (::libs::optim::io::MCallInfo& info)
{
  check_sat (info);
}


void
add_const_alu (::libs::optim::io::MCallInfo& info)
{
  check_consts (info);

  std::int16_t* dst    = info.dsts_[0].buf ();
  const auto    sdst   = info.dsts_[0].stride_;
  const auto    width  = info.dsts_[0].width_;
  const auto    height = info.dsts_[0].height_;
  std::int16_t* bdst   = dst;
  const auto    val    = info.params_.consts_[0][0];

  U3_XLOG_DBG (VTOLOG (val));
  for (std::uint32_t iy = 0; iy < height; ++iy)
  {
    for (std::uint32_t ix = 0; ix < width; ++ix)
    {
      bdst[ix] += val;
    }

    U3_FAST_MOVE_PTR (bdst, sdst);
  }
}

#  endif
#endif


#if defined(U3_CPU_X86)
#  ifndef SET_UNMASKDEST_FUNCT
#    ifndef SET_UNALIGNED_FUNCT

void
fill_func_abs_sub_sse2 (::libs::optim::io::MCallInfo& info)
{
  check_consts (info);

#      if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#      else
  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  std::int16_t loc_array_dx[8] = {
    info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0], info.params_.consts_[0][0]
  };

  std::int16_t loc_array_dy[8] = {
    info.params_.consts_[0][1], info.params_.consts_[0][1], info.params_.consts_[0][1], info.params_.consts_[0][1], info.params_.consts_[0][1], info.params_.consts_[0][1], info.params_.consts_[0][1], info.params_.consts_[0][1]
  };

  std::int16_t loc_array_const1234[8] = {
    1, 2, 3, 4, 5, 6, 7, 8
  };

  std::int32_t          bits_shift     = info.params_.ints_[0];
  const void*           dest           = info.dsts_[0].buf ();
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

    __asm
		{
			pushad;

#        define SSE_CONST_POINT_ZERO_X (xmm6)
#        define SSE_CONST_POINT_ZERO_Y (xmm7)
#        define SSE_CONST_1234 ([esi])
#        define SSE_CURRENT_OFF_Y (xmm5)
#        define SSE_CURRENT_SAD_Y_STRING (xmm1)
#        define SSE_TEMP_REG1 (xmm0)
#        define SSE_CONST_1or4 (xmm4)
#        define SSE_TEMP_REG3 (xmm3)
#        define SSE_CURRENT_OFF_X (xmm2)

			lea esi, loc_array_dx;
			movdqu SSE_CONST_POINT_ZERO_X, [esi];

			lea esi, loc_array_dy;
			movdqu SSE_CONST_POINT_ZERO_Y, [esi];

			pcmpeqw SSE_TEMP_REG1, SSE_TEMP_REG1;
			pxor SSE_CURRENT_OFF_Y, SSE_CURRENT_OFF_Y;
			psubsw SSE_CURRENT_OFF_Y, SSE_TEMP_REG1;

			pxor SSE_CONST_1or4, SSE_CONST_1or4;
			psubsw SSE_CONST_1or4, SSE_TEMP_REG1;

			lea esi, loc_array_const1234;

			mov edi, dest;
			mov ebx, stride_dest;
			mov ecx, height_element;

			mov edx, bits_shift;

			cycle1:

			mov eax, width_element;

			; calculate SAD for Y in mm1
			movdqa SSE_CURRENT_SAD_Y_STRING, SSE_CURRENT_OFF_Y;
			psubsw SSE_CURRENT_SAD_Y_STRING, SSE_CONST_POINT_ZERO_Y;

			movdqa SSE_TEMP_REG1, SSE_CURRENT_SAD_Y_STRING;
			psraw SSE_TEMP_REG1, 15;
			pxor SSE_CURRENT_SAD_Y_STRING, SSE_TEMP_REG1;
			psubsw SSE_CURRENT_SAD_Y_STRING, SSE_TEMP_REG1;

			movdqu SSE_CURRENT_OFF_X, SSE_CONST_1234;

			; convert from 1, 1, 1, 1 to 8, 8, 8, 8
			psllw SSE_CONST_1or4, 3;

			cycle2:

			; calculate SAD for X in mm0
			movdqa SSE_TEMP_REG1, SSE_CURRENT_OFF_X;
			psubsw SSE_TEMP_REG1, SSE_CONST_POINT_ZERO_X;

			movdqa SSE_TEMP_REG3, SSE_TEMP_REG1;
			psraw SSE_TEMP_REG3, 15;
			pxor SSE_TEMP_REG1, SSE_TEMP_REG3;
			psubsw SSE_TEMP_REG1, SSE_TEMP_REG3;

			; calculate summ SAD from x and y
			paddsw SSE_TEMP_REG1, SSE_CURRENT_SAD_Y_STRING;
			movd SSE_TEMP_REG3, edx;
			psraw SSE_TEMP_REG1, SSE_TEMP_REG3;

			movdqa[edi], SSE_TEMP_REG1;

			paddsw SSE_CURRENT_OFF_X, SSE_CONST_1or4;

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			; convert from 8, 8, 8, 8 to 1, 1, 1, 1
			psrlw SSE_CONST_1or4, 3;

			paddsw SSE_CURRENT_OFF_Y, SSE_CONST_1or4;

			sub ecx, 1;
			jg cycle1;

			popad;

#        undef SSE_CONST_POINT_ZERO_X
#        undef SSE_CONST_POINT_ZERO_Y
#        undef SSE_CONST_1234
#        undef SSE_CURRENT_OFF_Y
#        undef SSE_CURRENT_SAD_Y_STRING
#        undef SSE_TEMP_REG1
#        undef SSE_CONST_1or4
		}
#      endif
  return;
}
#    endif


#    ifndef SET_UNALIGNED_FUNCT

void
sat_2byte_sse2 (::libs::optim::io::MCallInfo& info)
{
  check_sat (info);

#      if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM) || 1

  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;
  __m128i               xmm1           = _mm_setzero_si128 ();

  for (std::uint32_t indy = 0; indy < height_element; ++indy)
  {
    for (std::uint32_t indx = 0; indx < sizeof (std::uint16_t) * width_element; indx += 16)
    {
      __m128i xmm0 = _mm_load_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx));
      xmm0         = _mm_packus_epi16 (xmm0, xmm1);
      xmm0         = _mm_unpacklo_epi8 (xmm0, xmm1);
      _mm_store_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
    }
    dest += stride_dest;
  }

#      else
  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			pxor xmm7, xmm7;

			cycle1:

			mov eax, edx;

			cycle2:

			movdqa xmm0, [edi];
			packuswb xmm0, xmm7;
			punpcklbw xmm0, xmm7;
			movdqa[edi], xmm0;

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#      endif
}


void
sat_2byte_avx1 (::libs::optim::io::MCallInfo& info)
{
  sat_2byte_sse2 (info);
}


void
sat_2byte_avx2 (::libs::optim::io::MCallInfo& info)
{
  sat_2byte_avx1 (info);
}

#    endif


#    ifdef SET_UNALIGNED_FUNCT
void
add_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
add_const_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check_consts (info);

  const std::int16_t loc_array_const[8] = {
    info.params_.consts_[0][0],
    info.params_.consts_[0][1],
    info.params_.consts_[0][2],
    info.params_.consts_[0][3],
    info.params_.consts_[0][0],
    info.params_.consts_[0][1],
    info.params_.consts_[0][2],
    info.params_.consts_[0][3]
  };

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM) || 1

  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;
  const __m128i         mask_dest      = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (mask_dest8));
  __m128i               consts         = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (loc_array_const));
  consts                               = _mm_and_si128 (consts, mask_dest);

  for (std::uint32_t indy = 0; indy < height_element; ++indy)
  {
    for (std::uint32_t indx = 0; indx < sizeof (std::uint16_t) * width_element; indx += 16)
    {
#      ifdef SET_UNALIGNED_FUNCT
      __m128i xmm0 = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (dest + indx));
#      else
      __m128i xmm0 = _mm_load_si128 (U3_CAST_REINTERPRET< const __m128i* > (dest + indx));
#      endif

      xmm0 = _mm_adds_epi16 (xmm0, consts);

#      ifdef SET_UNALIGNED_FUNCT
      _mm_store_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
#      else
      _mm_storeu_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
#      endif
    }
    // dest += width_element;
    dest += stride_dest;
  }

#    else
  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  // U3_XLOG_DEV (VTOLOG (stride_dest) + VTOLOG (width_element) + VTOLOG (height_element));

  __asm {
			pushad;

			lea edi, loc_array_const;
			movdqu xmm1, [edi];

			mov edi, mask_dest8;
			movdqu xmm7, [edi];

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			pand xmm1, xmm7;

			cycle1:

			mov eax, edx;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			paddsw xmm0, xmm1;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
}


#    ifndef SET_UNALIGNED_FUNCT
void
add_const_avx1 (::libs::optim::io::MCallInfo& info)
{
  add_const_unalign_dest_sse2 (info);
}
#    endif


#    ifndef SET_UNALIGNED_FUNCT
void
add_const_avx2 (::libs::optim::io::MCallInfo& info)
{
  add_const_avx1 (info);
}
#    endif


#    ifdef SET_UNALIGNED_FUNCT
void
sub_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
sub_const_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check_consts (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
  std::int16_t loc_array_const[8] = {
    info.params_.consts_[0][0], info.params_.consts_[0][1], info.params_.consts_[0][2], info.params_.consts_[0][3], info.params_.consts_[0][0], info.params_.consts_[0][1], info.params_.consts_[0][2], info.params_.consts_[0][3]
  };

  CHECK_ARG2 (0x0000000F);

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  const void*           dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			mov edi, mask_dest8;
			movdqu xmm7, [edi];

			lea edi, loc_array_const;
			movdqu xmm1, [edi];

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			pand xmm1, xmm7;

			cycle1:

			mov eax, edx;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			psubsw xmm0, xmm1;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
}


#    ifdef SET_UNALIGNED_FUNCT
void
mul_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
mul_const_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check_consts (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
  std::uint16_t loc_array_const[8] = {
    U3_CAST_UINT16 (info.params_.dest_mask_[0] ? info.params_.consts_[0][0] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[1] ? info.params_.consts_[0][1] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[2] ? info.params_.consts_[0][2] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[3] ? info.params_.consts_[0][3] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[4] ? info.params_.consts_[0][4] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[5] ? info.params_.consts_[0][5] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[6] ? info.params_.consts_[0][6] : U3_CAST_UINT16 (1)),
    U3_CAST_UINT16 (info.params_.dest_mask_[7] ? info.params_.consts_[0][7] : U3_CAST_UINT16 (1))
  };

  CHECK_ARG2 (0x0000000F);

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  const void*           dest           = info.dsts_[0].buf ();
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			lea edi, loc_array_const;
			movdqu xmm1, [edi];

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			cycle1:

			mov eax, edx;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			pmullw xmm0, xmm1;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
}


#    ifdef SET_UNALIGNED_FUNCT
void
mul_rshift_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
mul_rshift_const_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check_consts (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
  std::int16_t loc_array_const[8] = {
    info.params_.consts_[0][0], info.params_.consts_[0][1], info.params_.consts_[0][2], info.params_.consts_[0][3], info.params_.consts_[0][0], info.params_.consts_[0][1], info.params_.consts_[0][2], info.params_.consts_[0][3]
  };

  int bits_shift_right = info.params_.ints_[0];

  std::int16_t loc_array_rshift[8] = {
    (std::int16_t) bits_shift_right, 0, 0, 0, 0, 0, 0, 0
  };

  CHECK_ARG2 (0x0000000F);

  std::uint16_t loc_source_mask[8] = {
    U3_CAST_UINT16 (~info.params_.dest_mask_[0]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[1]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[2]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[3]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[4]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[5]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[6]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[7])
  };

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  const void*           dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			lea edi, loc_array_const;
			movdqu xmm1, [edi];

			mov edi, mask_dest8;
			movdqu xmm7, [edi];

			lea edi, loc_source_mask;
			movdqu xmm6, [edi];

			lea edi, loc_array_rshift;
			movdqu xmm5, [edi];

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			cycle1:

			mov eax, edx;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			movdqa xmm2, xmm0;
			pmullw xmm0, xmm1;
			pand xmm2, xmm6;
    // 22.08.2016 - corrected from logic to arifmetic
			psraw xmm0, xmm5;
			pand xmm0, xmm7;
			por xmm0, xmm2;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
}
#  endif


#  ifdef SET_UNALIGNED_FUNCT
#    ifdef SET_UNMASKDEST_FUNCT
void
sub_mul_rshift_add_const_unmask_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
sub_mul_rshift_add_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
#  else
#    ifdef SET_UNMASKDEST_FUNCT
void
sub_mul_rshift_add_const_unmask_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
sub_mul_rshift_add_const_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
#  endif
{
#  if 1

  return;

#  else
  check_consts (info);

  const std::int16_t* consts_mull_size8    = info.params_.consts_[0];
  const std::int16_t* consts_sub_add_size8 = info.params_.consts_[1];

  std::int16_t loc_array_const[8] = {
    info.params_.consts_[0][0], info.params_.consts_[0][1], info.params_.consts_[0][2], info.params_.consts_[0][3], info.params_.consts_[0][0], info.params_.consts_[0][1], info.params_.consts_[0][2], info.params_.consts_[0][3]
  };

  int bits_shift_right = info.params_.ints_[0];

  std::int16_t loc_array_rshift[8] = {
    (std::int16_t) bits_shift_right, 0, 0, 0, 0, 0, 0, 0
  };

  U3_ASSERT (consts_mull_size8);
  U3_ASSERT (consts_sub_add_size8);

  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (info.dsts_[0].buf ()));

#    ifndef SET_UNMASKDEST_FUNCT
  U3_ASSERT (info.params_.dest_mask_);
#    endif

#    ifndef SET_UNMASKDEST_FUNCT
  std::uint16_t loc_source_mask[8] = {
    U3_CAST_UINT16 (~info.params_.dest_mask_[0]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[1]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[2]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[3]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[4]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[5]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[6]),
    U3_CAST_UINT16 (~info.params_.dest_mask_[7])
  };
#    endif

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  const void*          dest           = info.dsts_[0].buf ();
  const std::uint16_t* mask_dest8     = info.params_.dest_mask_;
  const int            stride_dest    = info.dsts_[0].stride_;
  const int            width_element  = info.dsts_[0].width_;
  const int            height_element = info.dsts_[0].height_;

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
  __asm {
			pushad;

			mov edx, consts_sub_add_size8;
			movdqu xmm3, [edx];

			lea edi, loc_array_const;
			movdqu xmm1, [edi];

#      ifndef SET_UNMASKDEST_FUNCT
			mov edi, mask_dest8;
			movdqu xmm7, [edi];

			lea edi, loc_source_mask;
			movdqu xmm6, [edi];
#      endif

			lea edi, loc_array_rshift;
			movdqu xmm5, [edi];

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			cycle1:

			mov eax, edx;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif

#      ifndef SET_UNMASKDEST_FUNCT
			movdqa xmm2, xmm0;
#      endif
			psubsw xmm0, xmm3;
			pmullw xmm0, xmm1;

#      ifndef SET_UNMASKDEST_FUNCT
			pand xmm2, xmm6;
#      endif

			psraw xmm0, xmm5;
			paddsw xmm0, xmm3;

#      ifndef SET_UNMASKDEST_FUNCT
			pand xmm0, xmm7;
			por xmm0, xmm2;
#      endif

#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
#  endif
}


#  ifndef SET_UNMASKDEST_FUNCT

#    ifdef SET_UNALIGNED_FUNCT
void
comp_gt_const_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
comp_gt_const_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check_consts (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
  CHECK_ARG2 (0x0000000F);

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims (info.dsts_[0].stride_, info.dsts_[0].width_, loc_leak_stride, 8);

  const void*           dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;
  const std::int16_t*   consts1        = info.params_.consts_[0];

  __asm {
			pushad;

			mov edi, consts1;
			movdqu xmm1, [edi];

			mov edi, mask_dest8;
			movdqu xmm7, [edi];
			pcmpeqw xmm6, xmm6;
			pxor xmm6, xmm7;

			mov edi, dest;
			mov edx, width_element;
			mov ecx, height_element;
			mov ebx, stride_dest;

			cycle1:

			mov eax, edx;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			movdqa xmm2, xmm0;
			pand xmm2, xmm6;
			pcmpgtw xmm0, xmm1;
			pand xmm0, xmm7;
			por xmm0, xmm2;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
}
#  endif

#  undef CHECK_ARG2
#  undef CHECK_ARG2_FOR_SATURATION

#endif

}   // namespace libs::optim::s16bit::ops
