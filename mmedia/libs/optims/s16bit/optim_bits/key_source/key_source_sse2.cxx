/**
\file       key_source_sse2.cpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.11.2016
\project    u3_optim_libs_bits
*/
#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::bits::key_source
{
#  ifdef SET_UNALIGNED_FUNCT
void
un_sse2 (::libs::optim::io::MCallInfo& info)
#  else
void
sse2 (::libs::optim::io::MCallInfo& info)
#  endif
{
  check (info);

#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (info.srcs_[0].buf ()));
  U3_ASSERT (::libs::helpers::mem::check_align16 (info.dsts_[0].stride_));
  U3_ASSERT (::libs::helpers::mem::check_align16 (info.srcs_[0].stride_));

#    ifndef SET_UNALIGNED_FUNCT
  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (info.dsts_[0].buf ()));
#    endif

  std::uint16_t loc_ffff_mask[8] = {
    0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF, 0xFFFF
  };

  int loc_leak_stride = (info.dsts_[0].width_ >> 3);
  if (info.dsts_[0].width_ & 0x7)
    loc_leak_stride = loc_leak_stride + 1;
  loc_leak_stride = (loc_leak_stride << 4);

  info.dsts_[0].stride_ = info.dsts_[0].stride_ - loc_leak_stride;
  info.srcs_[0].stride_ = info.srcs_[0].stride_ - loc_leak_stride;

  info.dsts_[0].width_ = info.dsts_[0].width_ << 1;

  const void*          source         = info.srcs_[0].buf ();
  const void*          dest           = info.dsts_[0].buf ();
  const std::uint16_t* mask_dest8     = info.params_.dest_mask_;
  const int            stride_source  = info.srcs_[0].stride_;
  const int            stride_dest    = info.dsts_[0].stride_;
  const int            width_element  = info.dsts_[0].width_;
  const int            height_element = info.dsts_[0].height_;

  __asm {
			pushad;

			mov edi, mask_dest8;
			movdqu xmm6, [edi];

			lea edi, loc_ffff_mask;
			movdqu xmm5, [edi];

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
			movdqu xmm1, [esi];
#    else
			movdqa xmm0, [edi];
			movdqa xmm1, [esi];
#    endif
			pxor xmm2, xmm2;
			pcmpeqw xmm2, xmm1;
			movdqa xmm3, xmm2;
			pandn xmm3, xmm5;
			pand xmm3, xmm6;

			movdqa xmm2, xmm3;
			; 16.08.2016 - corrected xmm5 to xmm6;
			pandn xmm2, xmm6;

			pand xmm0, xmm2;
			pand xmm1, xmm3;
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

}   // namespace libs::optim::s16bit::bits::key_source
#endif
