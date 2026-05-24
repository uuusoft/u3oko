/**
\file				cond_3x3_sse2.cxx
\author			Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date				01.01.2017
\project		u3_optim_conv
*/

#if defined(U3_CPU_X86)

namespace libs::optim::s16bit::conv::cond
{
// OUT[x,y] = IN[x,y] * ( CONDT[x,y] < bound ? mask1 : mask2 )
#  ifdef MODUL_2D_CONV_IMPL
void
mod_cond_b3x3_sse2 (::libs::optim::io::MCallInfo& info)
#  else
void
cond_b3x3_sse2 (::libs::optim::io::MCallInfo& info)
#  endif
{
#  if defined(U3_CPU_X86_64) || defined(U3_OS_ANDROID) || defined(U3_CNTRL_FORCE_USE_X86_X64_ASM)
  U3_ASSERT_SIGNAL_I64;
  // U1UU_THROW_EXCEPTION("req intrinsic impl") );
#  else
  std::array< std::int16_t, 9 >* mask1           = 0;
  std::array< std::int16_t, 9 >* mask2           = 0;
  std::int16_t                   mul_koeff       = 0;
  std::int16_t                   bound_condition = 0;

  U3_CHECK (get_cond_conv_params (info, mask1, mask2, mul_koeff, bound_condition), "get cond params");

  std::int16_t mul_koeffs[8] = { mul_koeff, 0, 0, 0, 0, 0, mul_koeff, 0 };

  std::int16_t koeffs_mask_strs[4 * 8 * 3] = {
    (*mask1)[0],
    (*mask1)[1],
    (*mask1)[2],
    0,
    (*mask1)[0],
    (*mask1)[1],
    (*mask1)[2],
    0,
    (*mask1)[0],
    (*mask1)[1],
    (*mask1)[2],
    0,
    (*mask2)[0],
    (*mask2)[1],
    (*mask2)[2],
    0,
    (*mask2)[0],
    (*mask2)[1],
    (*mask2)[2],
    0,
    (*mask1)[0],
    (*mask1)[1],
    (*mask1)[2],
    0,
    (*mask2)[0],
    (*mask2)[1],
    (*mask2)[2],
    0,
    (*mask2)[0],
    (*mask2)[1],
    (*mask2)[2],
    0,


    (*mask1)[3],
    (*mask1)[4],
    (*mask1)[5],
    0,
    (*mask1)[3],
    (*mask1)[4],
    (*mask1)[5],
    0,
    (*mask1)[3],
    (*mask1)[4],
    (*mask1)[5],
    0,
    (*mask2)[3],
    (*mask2)[4],
    (*mask2)[5],
    0,
    (*mask2)[3],
    (*mask2)[4],
    (*mask2)[5],
    0,
    (*mask1)[3],
    (*mask1)[4],
    (*mask1)[5],
    0,
    (*mask2)[3],
    (*mask2)[4],
    (*mask2)[5],
    0,
    (*mask2)[3],
    (*mask2)[4],
    (*mask2)[5],
    0,


    (*mask1)[6],
    (*mask1)[7],
    (*mask1)[8],
    0,
    (*mask1)[6],
    (*mask1)[7],
    (*mask1)[8],
    0,
    (*mask1)[6],
    (*mask1)[7],
    (*mask1)[8],
    0,
    (*mask2)[6],
    (*mask2)[7],
    (*mask2)[8],
    0,
    (*mask2)[6],
    (*mask2)[7],
    (*mask2)[8],
    0,
    (*mask1)[6],
    (*mask1)[7],
    (*mask1)[8],
    0,
    (*mask2)[6],
    (*mask2)[7],
    (*mask2)[8],
    0,
    (*mask2)[6],
    (*mask2)[7],
    (*mask2)[8],
    0
  };

  std::uint32_t width           = info.srcs_[0].width_;    // - 2 * consts::short_from_edge;
  std::uint32_t height          = info.srcs_[0].height_;   // - 2 * consts::strings_from_edge;
  std::uint32_t count_str_bytes = ((((width & 0x7) ? width + 8 : width) >> 3) << 3) * sizeof (std::int16_t);
  std::uint32_t bytes_leak      = info.srcs_[0].stride_ - count_str_bytes;

  const std::int16_t* sbuf   = info.srcs_[0].buf ();
  std::int16_t*       dbuf   = info.dsts_[0].buf ();
  const std::int16_t* cbuf   = info.srcs_[1].buf ();
  std::uint32_t       stride = info.srcs_[0].stride_;

  __asm {
#    define REG_SOURCE_BUFFER esi
#    define REG_DESTINATION_BUFFER edi
#    define REG_CONDITION_BUFFER ebx
#    define REG_CYCLE_PIXEL_STRING ecx
#    define REG_STRIDE_BUFFERS eax
#    define REG_CYCLE_STRINGS edx
#    define REG_LEAKE_STRIDE_BUFFERS edx
#    define REG_TEMP1 edx
#    define REG_TEMP1_LOW_WORD dx

#    define SSEREG_KOEFF_MULL_RES xmm2

#    define SSEREG_TEMP1 xmm0
#    define SSEREG_TEMP2 xmm1
#    define SSEREG_TEMP4 xmm7

#    define SSEREG_STRING_TEMP_MASK xmm4

#    define SSEREG_CONDITION xmm5

			pushad;

			movdqu SSEREG_KOEFF_MULL_RES, mul_koeffs;

			mov REG_DESTINATION_BUFFER, dbuf;
			mov REG_SOURCE_BUFFER, sbuf;
			mov REG_CONDITION_BUFFER, cbuf;

			mov REG_STRIDE_BUFFERS, stride;

	cycle1 :

			mov REG_CYCLE_PIXEL_STRING, width;

	cycle2 :

#    define SSE_SELECT_MASK_FIRST_PIXEL_STRING(x)                                                                                                    \
      /*����� ����� ��� �������, ���� ������� �� ������-��������� ��� ������� ������� ������ ��������� ������ ���������� ������ ����� ����� ������*/ \
      /*�.�. �� ������ ���������� ����� ��� ����� �������� ��������� ��� ���������*/                                                                 \
      __asm movd REG_TEMP1, SSEREG_CONDITION __asm cmp REG_TEMP1_LOW_WORD, bound_condition __asm lea REG_TEMP1, koeffs_mask_strs __asm push REG_TEMP1 __asm jnge END_SELECT1_MASK##x __asm pop REG_TEMP1 __asm add REG_TEMP1, 32 __asm push REG_TEMP1

#    define SSE_SELECT_MASK_SECOND_PIXEL_STRING(x)                                                                                                   \
      /*����� ����� ��� �������, ���� ������� �� ������-��������� ��� ������� ������� ������ ��������� ������ ���������� ������ ����� ����� ������*/ \
      /*�.�. �� ������ ���������� ����� ��� ����� �������� ��������� ��� ���������*/                                                                 \
      __asm movd REG_TEMP1, SSEREG_CONDITION __asm shr REG_TEMP1, 16 __asm cmp REG_TEMP1_LOW_WORD, bound_condition __asm pop REG_TEMP1 __asm jnge END_SELECT2_MASK##x __asm add REG_TEMP1, 16

#    define SSE_ONE_PIXEL_STRING                                                                                                                                                                                                                                                                              \
      /*���������� ���������� ������� ����� � ������� ������*/                                                                                                                                                                                                                                                \
      __asm sub REG_SOURCE_BUFFER, REG_STRIDE_BUFFERS __asm movdqu SSEREG_TEMP1, [REG_SOURCE_BUFFER - 2] /*�������� ������� �������� � �������, ��� ��������� ��������� ������ 4 �����*/                                                                                                                      \
        __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP1, 68 /*���������� ����� � ������� ��������� ������ �������� �����*/                                                                                                                                                                                                                       \
        __asm pshufhw SSEREG_TEMP1,                                                                                                                                                                                                                                                                           \
        SSEREG_TEMP1, 57 __asm add REG_SOURCE_BUFFER, REG_STRIDE_BUFFERS /*��������� ������ ������ �����*/                                                                                                                                                                                                    \
        __asm movdqu SSEREG_STRING_TEMP_MASK,                                                                                                                                                                                                                                                                 \
        [REG_TEMP1] /*��������� �� ������ ������ ����� ��� ������� 4 �����*/                                                                                                                                                                                                                                  \
        __asm add        REG_TEMP1,                                                                                                                                                                                                                                                                           \
        64 __asm pmaddwd SSEREG_TEMP1, SSEREG_STRING_TEMP_MASK __asm movdqu SSEREG_TEMP2, [REG_SOURCE_BUFFER - 2] /*�������� ������� �������� � �������, ��� ��������� ��������� ������ 4 �����*/                                                                                                             \
        __asm pshufd SSEREG_TEMP2,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP2, 68 /*���������� ����� � ������� ��������� ������ �������� �����*/                                                                                                                                                                                                                       \
        __asm pshufhw SSEREG_TEMP2,                                                                                                                                                                                                                                                                           \
        SSEREG_TEMP2, 57 /*��������� ������ ������ �����*/                                                                                                                                                                                                                                                    \
        __asm movdqu SSEREG_STRING_TEMP_MASK,                                                                                                                                                                                                                                                                 \
        [REG_TEMP1] /*��������� �� ������ ������ ����� ��� ������� 4 �����*/                                                                                                                                                                                                                                  \
        __asm add        REG_TEMP1,                                                                                                                                                                                                                                                                           \
        64 __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING_TEMP_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqu SSEREG_TEMP2, [REG_SOURCE_BUFFER + REG_STRIDE_BUFFERS - 2] /*�������� ������� �������� � �������, ��� ��������� ��������� ������ 4 �����*/                                                 \
        __asm pshufd SSEREG_TEMP2,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP2, 68 /*���������� ����� � ������� ��������� ������ �������� �����*/                                                                                                                                                                                                                       \
        __asm pshufhw SSEREG_TEMP2,                                                                                                                                                                                                                                                                           \
        SSEREG_TEMP2, 57 /*��������� ������ ������ �����*/                                                                                                                                                                                                                                                    \
        __asm movdqu              SSEREG_STRING_TEMP_MASK,                                                                                                                                                                                                                                                    \
        [REG_TEMP1] __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING_TEMP_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqa SSEREG_TEMP2, SSEREG_TEMP1 __asm psrldq SSEREG_TEMP2, 4 __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 /* 11.05.2016 ��������� ��������� �� ����������� � ��������� ������� ����� �����*/ \
        __asm packssdw             SSEREG_TEMP1,                                                                                                                                                                                                                                                              \
        SSEREG_TEMP1 __asm pmaddwd SSEREG_TEMP1, SSEREG_KOEFF_MULL_RES __asm psrad SSEREG_TEMP1, U3_SHIFT_MUL_KOEFF_CONVOLUTION /*������������ ���������*/                                                                                                                                                    \
        __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                            \
        SSEREG_TEMP1, 12 __asm packssdw SSEREG_TEMP1, SSEREG_TEMP1 /*��������� �������� � �������� mmx ��� ����������� ���������� � ������*/                                                                                                                                                                  \
        __asm psrldq   SSEREG_TEMP4,                                                                                                                                                                                                                                                                          \
        4 __asm pslldq SSEREG_TEMP1, 12 __asm por SSEREG_TEMP4, SSEREG_TEMP1 /*��������� �� ��������� �������-����� �� ������� ������*/                                                                                                                                                                       \
        __asm add REG_SOURCE_BUFFER,                                                                                                                                                                                                                                                                          \
        4 /*��������� �� �������� �������� � ������-��������� ��� ��������� ���� ��������-����*/                                                                                                                                                                                                              \
        __asm psrldq SSEREG_CONDITION,                                                                                                                                                                                                                                                                        \
        4

#    if 0
#      define SSE_ONE_PIXEL_STRING                                                                                                                                                                                                                                                                                                         \
        /*���������� ����� � ������� ��������� ������ �������� �����*/                                                                                                                                                                                                                                                                     \
        __asm pshufhw SSEREG_TEMP2, SSEREG_TEMP2, 57 __asm pmaddwd SSEREG_TEMP2, SSEREG_STRING3_MASK __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 __asm movdqa SSEREG_TEMP2, SSEREG_TEMP1 __asm psrldq SSEREG_TEMP2, 4 __asm paddd SSEREG_TEMP1, SSEREG_TEMP2 /* 11.05.2016 ��������� ��������� �� ����������� � ��������� ������� ����� �����*/ \
          __asm packssdw             SSEREG_TEMP1,                                                                                                                                                                                                                                                                                         \
          SSEREG_TEMP1 __asm pmaddwd SSEREG_TEMP1, SSEREG_KOEFF_MULL_RES __asm psrad SSEREG_TEMP1, U3_SHIFT_MUL_KOEFF_CONVOLUTION /*������������ ���������*/                                                                                                                                                                               \
          __asm pshufd SSEREG_TEMP1,                                                                                                                                                                                                                                                                                                       \
          SSEREG_TEMP1, 12 __asm packssdw SSEREG_TEMP1, SSEREG_TEMP1 /*��������� �� ��������� ��������*/                                                                                                                                                                                                                                   \
          __asm psrldq   SSEREG_TEMP4,                                                                                                                                                                                                                                                                                                     \
          4 __asm pslldq SSEREG_TEMP1, 12 __asm por SSEREG_TEMP4, SSEREG_TEMP1 /*������������ �� �������� ��� �������-����� � ���������*/                                                                                                                                                                                                  \
          __asm add REG_SOURCE_BUFFER,                                                                                                                                                                                                                                                                                                     \
          4
#    endif

			movdqu SSEREG_CONDITION, [REG_CONDITION_BUFFER];

			pxor SSEREG_TEMP4, SSEREG_TEMP4;

			SSE_SELECT_MASK_FIRST_PIXEL_STRING (1 );
			END_SELECT1_MASK1:
			SSE_SELECT_MASK_SECOND_PIXEL_STRING (1 );
			END_SELECT2_MASK1:
			SSE_ONE_PIXEL_STRING;

			SSE_SELECT_MASK_FIRST_PIXEL_STRING (2 );
			END_SELECT1_MASK2:
			SSE_SELECT_MASK_SECOND_PIXEL_STRING (2 );
			END_SELECT2_MASK2:
			SSE_ONE_PIXEL_STRING;

			SSE_SELECT_MASK_FIRST_PIXEL_STRING ( 3);
			END_SELECT1_MASK3:
			SSE_SELECT_MASK_SECOND_PIXEL_STRING ( 3);
			END_SELECT2_MASK3:
			SSE_ONE_PIXEL_STRING;

			SSE_SELECT_MASK_FIRST_PIXEL_STRING (4 );
			END_SELECT1_MASK4:
			SSE_SELECT_MASK_SECOND_PIXEL_STRING (4 );
			END_SELECT2_MASK4:
			SSE_ONE_PIXEL_STRING;

#    ifdef MODUL_2D_CONV_IMPL
			pxor SSEREG_TEMP1, SSEREG_TEMP1;
			pxor SSEREG_TEMP2, SSEREG_TEMP2;
			psubusw SSEREG_TEMP2, SSEREG_TEMP4;
			psubusw SSEREG_TEMP4, SSEREG_TEMP1;
			por SSEREG_TEMP4, SSEREG_TEMP2;
#    else
#    endif
			movdqu[REG_DESTINATION_BUFFER], SSEREG_TEMP4;

			add REG_DESTINATION_BUFFER, 16;
			add REG_CONDITION_BUFFER, 16;

			sub REG_CYCLE_PIXEL_STRING, 8;
			jg cycle2;

			mov REG_LEAKE_STRIDE_BUFFERS, bytes_leak;

			add REG_SOURCE_BUFFER, REG_LEAKE_STRIDE_BUFFERS;
			add REG_DESTINATION_BUFFER, REG_LEAKE_STRIDE_BUFFERS;
			add REG_CONDITION_BUFFER, REG_LEAKE_STRIDE_BUFFERS;

			mov REG_CYCLE_STRINGS, height;
			sub REG_CYCLE_STRINGS, 1;
			mov height, REG_CYCLE_STRINGS;

			jg cycle1;

			popad;
			emms;

#    undef SSE_SELECT_MASK_FIRTS_PIXEL_STRING
#    undef SSE_SELECT_MASK_SECOND_PIXEL_STRING
#    undef SSE_ONE_PIXEL_STRING

#    undef REG_SOURCE_BUFFER
#    undef REG_DESTINATION_BUFFER
#    undef REG_CONDITION_BUFFER
#    undef REG_CYCLE_PIXEL_STRING
#    undef REG_CYCLE_STRINGS
#    undef REG_STRIDE_BUFFERS
#    undef REG_LEAKE_STRIDE_BUFFERS
#    undef REG_TEMP1
#    undef REG_TEMP1_LOW_WORD

#    undef SSEREG_KOEFF_MULL_RES
#    undef SSEREG_TEMP1
#    undef SSEREG_TEMP2

#    undef SSEREG_STRING_TEMP_MASK
#    undef SSEREG_CONDITION
  }
#  endif
}
}   // namespace libs::optim::s16bit::conv::cond

#endif
