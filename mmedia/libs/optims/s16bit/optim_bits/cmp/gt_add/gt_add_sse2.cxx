/**
\file       gt_add_sse2.cxx
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016

\project    u3_optim_libs_bits
\brief
*/

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::bits::cmp::gt_add
{
#  ifndef SET_UNALIGNED_FUNCT
void
sse2 (::libs::optim::io::MCallInfo& info)
#  else
void
udest_sse2 (::libs::optim::io::MCallInfo& info)
#  endif
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  picter_dim_type number_sub_pixel_x = 0;
  picter_dim_type number_sub_pixel_y = 0;

  picter_dim_type leak_stride_source = 0;
  picter_dim_type leak_stride_dest   = 0;

  auto& dst = info.dsts_[0];
  auto& src = info.srcs_[0];

  calc_dest_source_dims (
    dst.stride_,
    dst.stride_,
    dst.width_,
    dst.height_,
    8,
    number_sub_pixel_x,
    number_sub_pixel_y,
    leak_stride_source,
    leak_stride_dest);

#    ifndef SET_UNALIGNED_FUNCT
  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (dst.buf ()));
  U3_ASSERT (::libs::helpers::mem::check_align16 (dst.stride_));
#    endif

  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (src.buf ()));
  U3_ASSERT (::libs::helpers::mem::check_align16 (src.stride_));

  const void*          source     = src.buf ();
  const void*          dest       = dst.buf ();
  const std::uint16_t* mask_dest8 = info.params_.dest_mask_;
  const std::int16_t*  consts1    = info.params_.consts_[0];

    __asm
		{
			; eax - leak_stride_source;
			; ebx - cycle for col;
			; ecx - cycle for row;
			; edx - source;
			; edi - leak_stride_dest;
			; esi - dest;
			; xmm0 - current string source;
			; xmm1 - current string dest;
			; xmm2 -;
			; xmm3 -;
			; xmm4 -;
			; xmm5 - current cmp bound;
			; xmm6 - mask source equal inv mm7;
			; xmm7 - mask dest;

			pushad;

			mov eax, consts1;
			movdqu xmm5, [eax];

			mov eax, mask_dest8;
			movdqu xmm7, [eax];

			movdqa xmm6, xmm7;
			pcmpeqw xmm0, xmm0;
			pxor xmm6, xmm0;

			mov eax, leak_stride_source;
			mov edi, leak_stride_dest;
			mov ecx, number_sub_pixel_y;
			mov edx, source;
			mov esi, dest;

			cycle_row:
			mov ecx, number_sub_pixel_x;

			cycle_col:
			movdqa xmm0, [edx];

#    ifndef SET_UNALIGNED_FUNCT
			movdqa xmm1, [esi];
#    else
			movdqu xmm1, [esi];
#    endif

			movdqa xmm2, xmm0;
			pcmpgtw xmm2, xmm5;
			pand xmm0, xmm2;
			movdqa xmm2, xmm1;
			paddsw xmm2, xmm0;
			pand xmm2, xmm7;
			pand xmm1, xmm6;
			por xmm1, xmm2;

    // saved result
#    ifndef SET_UNALIGNED_FUNCT
			movdqa[esi], xmm1;
#    else
			movdqu[esi], xmm1;
#    endif

			//go to next
			add edx, 16;
			add esi, 16;

			sub ecx, 1;
			; 24.05.2016;
			jg cycle_col;

			add edx, eax;
			add esi, edi;

			sub number_sub_pixel_y, 1;
			; 24.05.2016;
			jg cycle_row;

			popad;
		}
#  endif
}
}   // namespace libs::optim::s16bit::bits::cmp::gt_add

#endif
