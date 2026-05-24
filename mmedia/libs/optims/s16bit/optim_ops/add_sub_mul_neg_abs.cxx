/**
\file       add_sub_mul_neg_abs.cxx
\date       26.07.2016
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_ops
*/
#include "add_sub_mul_neg_abs.hpp"

namespace libs::optim::s16bit::ops
{
#ifndef U3_CHECK_FAST_ARGS_OPTIM_FUNCTS

#  ifndef ALLREADEY_OUTPUT_U3_CHECK_FAST_ARGS_OPTIM_FUNCTS
#    define ALLREADEY_OUTPUT_U3_CHECK_FAST_ARGS_OPTIM_FUNCTS
#  endif

#  ifdef SET_UNALIGNED_FUNCT
#    define CHECK_ARG2(mask_dest)                                                                                                                              \
      if ((U3_CAST_REINTERPRET< long long > (info.srcs_[0].buf ()) & mask_dest) || (info.dsts_[0].stride_ & mask_dest) || (info.srcs_[0].stride_ & mask_dest)) \
      {                                                                                                                                                        \
        U3_ASSERT_SIGNAL ("failed");                                                                                                                           \
        return;                                                                                                                                                \
      }
#  else
#    define CHECK_ARG2(mask_dest)                                                                                                                                                                                                       \
      if ((U3_CAST_REINTERPRET< long long > (info.dsts_[0].buf ()) & mask_dest) || (U3_CAST_REINTERPRET< long long > (info.srcs_[0].buf ()) & mask_dest) || (info.dsts_[0].stride_ & mask_dest) || (info.srcs_[0].stride_ & mask_dest)) \
      {                                                                                                                                                                                                                                 \
        U3_ASSERT_SIGNAL ("failed");                                                                                                                                                                                                    \
        return;                                                                                                                                                                                                                         \
      }
#  endif
#else
#  define CHECK_ARG2(mask_dest)
#endif


#if !defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) && !defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
#  ifndef SET_UNALIGNED_FUNCT
void
sub_abs_diff_alu (::libs::optim::io::MCallInfo& info)
{
  check (info);

  const std::int16_t*   source        = info.srcs_[0].buf ();
  std::int16_t*         dest          = info.dsts_[0].buf ();
  const picter_dim_type stride_source = info.srcs_[0].stride_;
  const picter_dim_type stride_dest   = info.dsts_[0].stride_;
  const picter_dim_type width         = info.dsts_[0].width_;
  const picter_dim_type height        = info.dsts_[0].height_;
  const std::int16_t*   bsource       = source;
  std::int16_t*         bdest         = dest;

  for (picter_dim_type indxy = 0; indxy < height; ++indxy)
  {
    for (picter_dim_type indxx = 0; indxx < width; ++indxx)
    {
      int diff     = bdest[indxx] > bsource[indxx] ? bdest[indxx] - bsource[indxx] : bsource[indxx] - bdest[indxx];
      bdest[indxx] = diff;
    }

    U3_FAST_MOVE_CPTR (bsource, stride_source);
    U3_FAST_MOVE_PTR (bdest, stride_dest);
  }
}

#  endif
#endif


#if defined(U3_CPU_X86)

#  if !defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) && !defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)

#    ifdef SET_UNALIGNED_FUNCT
void
add_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
add_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM) || 1

  const std::uint8_t*   source         = info.srcs_[0].ubuf ();
  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_source  = info.srcs_[0].stride_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;
  const __m128i         mask_dest      = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (mask_dest8));

  for (std::uint32_t indy = 0; indy < height_element; ++indy)
  {
    for (std::uint32_t indx = 0; indx < sizeof (std::uint16_t) * width_element; indx += 16)
    {
#      ifdef SET_UNALIGNED_FUNCT
      __m128i xmm0 = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (dest + indx));
#      else
      __m128i xmm0 = _mm_load_si128 (U3_CAST_REINTERPRET< const __m128i* > (dest + indx));
#      endif

      __m128i xmm1 = _mm_load_si128 (U3_CAST_REINTERPRET< const __m128i* > (source + indx));
      xmm1         = _mm_and_si128 (xmm1, mask_dest);
      xmm0         = _mm_adds_epi16 (xmm0, xmm1);

#      ifdef SET_UNALIGNED_FUNCT
      _mm_store_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
#      else
      _mm_storeu_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
#      endif
    }
    source += stride_source;
    dest += stride_dest;
  }

#    else

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims_source (
    info.dsts_[0].stride_,
    info.srcs_[0].stride_,
    info.dsts_[0].width_,
    loc_leak_stride,
    8);

  const std::uint8_t*   source         = info.srcs_[0].ubuf ();
  std::uint8_t*         dest           = info.dsts_[0].ubuf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_source  = info.srcs_[0].stride_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;


  __asm {
			pushad;

			mov edi, mask_dest8;
			movdqu xmm7, [edi];

			mov edi, dest;
			mov esi, source;
			mov ebx, stride_dest;
			mov edx, stride_source;

			mov ecx, height_element;

			cycle1:

			mov eax, width_element;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			movdqa xmm1, [esi];
			pand xmm1, xmm7;
			paddsw xmm0, xmm1;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add esi, 16;
			add edi, 16;

			sub eax, 16;
			jg cycle2;


			add edi, ebx;
			add esi, edx;

			sub ecx, 1;
			jg cycle1;


			popad;
  }
#    endif
}


#    ifdef SET_UNALIGNED_FUNCT
void
sub_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
sub_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check (info);
  CHECK_ARG2 (0x0000000F);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims_source (
    info.dsts_[0].stride_,
    info.srcs_[0].stride_,
    info.dsts_[0].width_,
    loc_leak_stride,
    8);

  const void*           source         = info.srcs_[0].buf ();
  const void*           dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_source  = info.srcs_[0].stride_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			mov edi, mask_dest8;
			movdqu xmm7, [edi];

			mov edi, dest;
			mov esi, source;
			mov ebx, stride_dest;
			mov edx, stride_source;

			mov ecx, height_element;

			cycle1:

			mov eax, width_element;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			movdqa xmm1, [esi];
			pand xmm1, xmm7;
			psubsw xmm0, xmm1;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add esi, 16;
			add edi, 16;

			sub eax, 16;
			jg cycle2;


			add edi, ebx;
			add esi, edx;

			sub ecx, 1;
			jg cycle1;


			popad;
  }
#    endif
}


#    ifdef SET_UNALIGNED_FUNCT
void
sub_abs_diff_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
sub_abs_diff_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM) || 1
  auto                  source           = info.srcs_[0].ubuf ();
  auto                  dest             = info.dsts_[0].ubuf ();
  const std::uint16_t*  mask_dest8       = info.params_.dest_mask_;
  const picter_dim_type stride_source    = info.srcs_[0].stride_;
  const picter_dim_type stride_dest      = info.dsts_[0].stride_;
  const picter_dim_type width_element    = info.dsts_[0].width_;
  const picter_dim_type height_element   = info.dsts_[0].height_;
  const __m128i         mask_dest        = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (mask_dest8));
  const __m128i         allxffff         = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (::libs::optim::s16bit::consts::us_all_xffff));
  const __m128i         invert_mask_dest = _mm_andnot_si128 (mask_dest, allxffff);
  // const __m128i         invert_mask_dest = _mm_andnot_si128 (mask_dest, mask_dest);

  for (std::uint32_t indy = 0; indy < height_element; ++indy)
  {
    for (std::uint32_t indx = 0; indx < sizeof (std::uint16_t) * width_element; indx += 16)
    {
#      ifdef SET_UNALIGNED_FUNCT
      // movdqu  xmm0, [edi];
      __m128i xmm0 = _mm_loadu_si128 (U3_CAST_REINTERPRET< const __m128i* > (dest + indx));
#      else
      // movdqa  xmm0, [edi];
      __m128i xmm0 = _mm_load_si128 (U3_CAST_REINTERPRET< const __m128i* > (dest + indx));
#      endif

      __m128i xmm1 = _mm_load_si128 (U3_CAST_REINTERPRET< const __m128i* > (source + indx));
      // movdqa  xmm2, xmm0;
      __m128i xmm2 = xmm0;
      // movdqa  xmm4, xmm1;
      __m128i xmm4 = xmm1;
      // psubusw xmm4, xmm0;
      xmm4 = _mm_subs_epu16 (xmm4, xmm0);
      // psubusw xmm0, xmm1;
      xmm0 = _mm_subs_epu16 (xmm0, xmm1);
      // por     xmm0, xmm4;
      xmm0 = _mm_or_si128 (xmm0, xmm4);
      // pand    xmm0, xmm7;
      xmm0 = _mm_and_si128 (xmm0, mask_dest);
      // pand    xmm2, xmm6;
      xmm2 = _mm_and_si128 (xmm2, invert_mask_dest);
      // por     xmm0, xmm2;
      xmm0 = _mm_or_si128 (xmm0, xmm2);

#      ifdef SET_UNALIGNED_FUNCT
      // movdqu[edi], xmm0;
      _mm_store_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
#      else
      // movdqa[edi], xmm0;
      _mm_storeu_si128 (U3_CAST_REINTERPRET< __m128i* > (dest + indx), xmm0);
#      endif
    }
    source += stride_source;
    dest += stride_dest;
  }

#    else

  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims_source (
    info.dsts_[0].stride_,
    info.srcs_[0].stride_,
    info.dsts_[0].width_,
    loc_leak_stride,
    8);

  const std::int16_t*   source         = info.srcs_[0].buf ();
  std::int16_t*         dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_source  = info.srcs_[0].stride_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			mov edi, mask_dest8;
			movdqu xmm7, [edi];
			pcmpeqw xmm6, xmm6;
			pxor xmm6, xmm7;

			mov edi, dest;
			mov esi, source;
			mov ebx, stride_dest;
			mov edx, stride_source;

			mov ecx, height_element;

			cycle1:

			mov eax, width_element;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			movdqa xmm1, [esi];

			movdqa xmm2, xmm0;
			movdqa xmm4, xmm1;
			psubusw xmm4, xmm0;
			psubusw xmm0, xmm1;
			por xmm0, xmm4;
			pand xmm0, xmm7;
			pand xmm2, xmm6;
			por xmm0, xmm2;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add esi, 16;
			add edi, 16;

			sub eax, 16;
			jg cycle2;

			add edi, ebx;
			add esi, edx;

			sub ecx, 1;
			jg cycle1;

			popad;
  }
#    endif
}


#    ifndef SET_UNALIGNED_FUNCT
void
sub_abs_diff_avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  sub_abs_diff_unalign_dest_sse2 (info);
}
#    endif


#    ifndef SET_UNALIGNED_FUNCT
void
sub_abs_diff_avx2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  sub_abs_diff_avx1 (info);
}
#    endif


#    ifdef SET_UNALIGNED_FUNCT
void
mul_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
void
mul_sse2 (::libs::optim::io::MCallInfo& info)
#    endif
{
  check (info);

#    if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#    else
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

  calc_dest_dims_source (
    info.dsts_[0].stride_,
    info.srcs_[0].stride_,
    info.dsts_[0].width_,
    loc_leak_stride,
    8);

  const void*           source         = info.srcs_[0].buf ();
  const void*           dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_source  = info.srcs_[0].stride_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			lea edi, loc_source_mask;
			movdqu xmm7, [edi];

			mov edi, mask_dest8;
			movdqu xmm6, [edi];


			mov edi, dest;
			mov esi, source;
			mov ebx, stride_dest;
			mov edx, stride_source;

			mov ecx, height_element;

			cycle1:

			mov eax, width_element;

			cycle2:

#      ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#      else
			movdqa xmm0, [edi];
#      endif
			movdqa xmm1, xmm0;
			pmullw xmm0, [esi];
    // 07.06.2016
			pand xmm0, xmm6;
			pand xmm1, xmm7;
			por xmm0, xmm1;
#      ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#      else
			movdqa[edi], xmm0;
#      endif

			add esi, 16;
			add edi, 16;

			sub eax, 16;
			jg cycle2;


			add edi, ebx;
			add esi, edx;

			sub ecx, 1;
			jg cycle1;


			popad;
  }
#    endif
}
#  endif


#  ifdef SET_UNALIGNED_FUNCT
#    if !defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) && !defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
void
mul_rshift_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    elif defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord)
void
mul_neg_rshift_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    elif defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
void
mul_neg2_rshift_unalign_dest_sse2 (::libs::optim::io::MCallInfo& info)
#    else
#      error "Need defined type file"
#    endif
#  else
#    if !defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) && !defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
void
mul_rshift_sse2 (::libs::optim::io::MCallInfo& info)
#    elif defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord)
void
mul_neg_rshift_sse2 (::libs::optim::io::MCallInfo& info)
#    elif defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
void
mul_neg2_rshift_sse2 (::libs::optim::io::MCallInfo& info)
#    else
#      error "Need defined type file"
#    endif
#  endif
{
  check_rshifts (info);

#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  picter_dim_type loc_leak_stride = 0;

  calc_dest_dims_source (
    info.dsts_[0].stride_,
    info.srcs_[0].stride_,
    info.dsts_[0].width_,
    loc_leak_stride,
    8);

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

  const void*           source         = info.srcs_[0].buf ();
  const void*           dest           = info.dsts_[0].buf ();
  const std::uint16_t*  mask_dest8     = info.params_.dest_mask_;
  const picter_dim_type stride_source  = info.srcs_[0].stride_;
  const picter_dim_type stride_dest    = info.dsts_[0].stride_;
  const picter_dim_type width_element  = info.dsts_[0].width_;
  const picter_dim_type height_element = info.dsts_[0].height_;
  const std::int16_t*   consts1        = info.params_.consts_[0];

#    if defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) || defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
  const std::int16_t* consts2 = info.params_.consts_[1];
#    endif

  __asm {
			pushad;

			lea edi, loc_source_mask;
			movdqu xmm7, [edi];

			mov edi, mask_dest8;
			movdqu xmm6, [edi];

			mov edi, consts1;
			movdqu xmm5, [edi];

#    if defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) || defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
			mov edi, consts2;
			movdqu xmm3, [edi];
#    endif

			mov edi, dest;
			mov esi, source;
			mov ebx, stride_dest;
			mov edx, stride_source;

			mov ecx, height_element;

			cycle1:

			mov eax, width_element;

			cycle2:

#    ifdef SET_UNALIGNED_FUNCT
			movdqu xmm0, [edi];
#    else
			movdqa xmm0, [edi];
#    endif

			movdqa xmm1, xmm0;
#    if !defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) && !defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
			pmullw xmm0, [esi];
#    elif defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord)
			movdqa xmm4, xmm3;
			psubsw xmm4, [esi];
			pmullw xmm0, xmm4;
#    elif defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)
			movdqa xmm4, xmm3;
			psubsw xmm4, xmm0;
			pmullw xmm4, [esi];
			movdqa xmm0, xmm4;
#    else
#      error "Need defined type file"
#    endif

			psraw xmm0, xmm5;
			pand xmm0, xmm6;
			pand xmm1, xmm7;
			por xmm0, xmm1;

#    ifdef SET_UNALIGNED_FUNCT
			movdqu[edi], xmm0;
#    else
			movdqa[edi], xmm0;
#    endif

			add esi, 16;
			add edi, 16;

			sub eax, 16;
			jg cycle2;


			add edi, ebx;
			add esi, edx;

			sub ecx, 1;
			jg cycle1;


			popad;
  }
#  endif
}


#  if !defined(ADD_SUB_MULL_SWORD_MullNegRShiftSignedWord) && !defined(ADD_SUB_MULL_SWORD_MullNeg2RShiftSignedWord)

#    ifndef SET_UNALIGNED_FUNCT
void
mul_rshift_avx1 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  mul_rshift_unalign_dest_sse2 (info);
}
#    endif


#    ifndef SET_UNALIGNED_FUNCT
void
mul_rshift_avx2 (::libs::optim::io::MCallInfo& info)
{
  U3_ASSERT_TODO_OPTIM;
  mul_rshift_avx1 (info);
}
#    endif

#  endif


#  undef CHECK_ARG2
#endif

}   // namespace libs::optim::s16bit::ops
