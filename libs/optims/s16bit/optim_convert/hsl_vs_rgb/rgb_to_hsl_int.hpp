#pragma once
/**
\file       rgb_to_hsl_int.hpp
\author     Anton Erashov /eai/ skype: ytkoduff; emails: erashov@uuusoft.com, erashov2004@yandex.ru
\date       24.11.2016
\copyright  www.uuusoft.com
\project    uuu_optim_convert
\brief      empty brief
*/

namespace libs { namespace optim { namespace s16bit { namespace convert { namespace hsl_vs_rgb {
/**
  \brief  empty brief
  */
inline bool
check_rgb2hsl (::libs::optim::MCallInfo& _info)
{
  if (3 != _info.dsts_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if (1 != _info.srcs_.size ())
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  const ::libs::optim::io::ProxyBuff& _h   = _info.dsts_[0];
  const ::libs::optim::io::ProxyBuff& _s   = _info.dsts_[1];
  const ::libs::optim::io::ProxyBuff& _l   = _info.dsts_[2];
  const ::libs::optim::io::ProxyBuff& _rgb = _info.srcs_[0];

  if ((_h.width_ != _s.width_) || (_h.width_ != _l.width_) || (_h.width_ != _rgb.width_))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  if ((_h.height_ != _s.height_) || (_h.height_ != _l.height_) || (_h.height_ != _rgb.height_))
    {
      UASSERT_SIGNAL ("failed");
      return false;
    }

  return true;
}
}}}}}      // namespace libs::optim::s16bit::convert::hsl_vs_rgb


#if !defined(RGB2HSL_PREFIX)
#define RGB2HSL_PREFIX(_size)                                                                                \
                                                                                                             \
  CHECK_CALL (check_rgb2hsl (_info), "failde check rgb2hsl");                                                \
  const unsigned int  _ppc            = _size;                                                               \
  const std::size_t   _width          = _info.srcs_[0].width_;                                               \
  const std::size_t   _height         = _info.srcs_[0].height_;                                              \
  short*              _h              = _info.dsts_[0].buff ();                                              \
  short*              _s              = _info.dsts_[1].buff ();                                              \
  short*              _l              = _info.dsts_[2].buff ();                                              \
  const unsigned int* _rgb24          = UUU_MEM_CAST<const unsigned int*> (_info.srcs_[0].ubuff ());         \
  const unsigned int  _raw_cycle      = _width / _ppc;                                                       \
  const unsigned int  _cycle          = (_raw_cycle * _ppc < _width) ? _raw_cycle + 1 : _raw_cycle;          \
  const unsigned int  _leak_rgb       = _info.srcs_[0].stride_ - _cycle * _ppc * sizeof (unsigned char) * 3; \
  const unsigned int  _req_stride_hsl = _cycle * sizeof (unsigned short) * _ppc;                             \
  const unsigned int  _leak_hsl       = _info.dsts_[0].stride_ - _req_stride_hsl;

#endif


#if !defined(SPLIT_RGB24_SSE2_DEFINE_REGS)
#define SPLIT_RGB24_SSE2_DEFINE_REGS                              \
                                                                  \
  const __m128i _zero = _mm_setzero_si128 ();                     \
  __m128i       _low16;                                           \
  __m128i       _low16_2;                                         \
  __m128i       _hi16;                                            \
  __m128i       _hi16_2;                                          \
  const __m128i _mask1 = _mm_setr_epi32 (0xFF, 0xFF, 0x00, 0x00); \
  const __m128i _mask2 = _mm_setr_epi32 (0x00, 0x00, 0xFF, 0xFF);
#endif


#if !defined(SPLIT_RGB24_SSE2)
#define SPLIT_RGB24_SSE2(_reg_rgb24, _ir8, _ig8, _ib8)                                                               \
                                                                                                                     \
  _reg_rgb24 = _mm_shuffle_epi32 (_reg_rgb24, 0x94);  /*BOG0R0B1 G1R1B2G2 G1R1B2G2 R2B3G3R3,  10 01 01 00=0x94*/     \
  _low16     = _mm_unpacklo_epi8 (_reg_rgb24, _zero); /*B000G000 R000B100 G100R100 B200G200*/                        \
  _low16_2   = _mm_shuffle_epi32 (_low16, 0xC9);      /*R000B100 G100R100 B000G000 B200G200,  11 00 10 01=0xc9*/     \
  /*R-------------------------------------------------------------------------------------------------------------*/ \
  _ir8    = _mm_shufflelo_epi16 (_low16_2, 0x30);  /*R0xxxxxx R1xxxxxx xxxxxxxx xxxxxxxx,  00 11 00 00=0x30*/        \
  _ir8    = _mm_and_si128 (_ir8, _mask1);          /*R0000000 R1000000 00000000 00000000*/                           \
  _hi16   = _mm_unpackhi_epi8 (_reg_rgb24, _zero); /*G100R100 B200G200 R200B300 G300R300*/                           \
  _hi16_2 = _mm_shufflehi_epi16 (_hi16, 0x30);     /*xxxxxxxx xxxxxxxx R2xxxxxx R3xxxxxx,  00 11 00 00=0x30*/        \
  _hi16_2 = _mm_and_si128 (_hi16_2, _mask2);       /*00000000 00000000 R2000000 R3000000*/                           \
  _ir8    = _mm_or_si128 (_ir8, _hi16_2);          /*R0000000 R1000000 R2000000 R3000000*/                           \
  /*G-------------------------------------------------------------------------------------------------------------*/ \
  _low16_2 = _mm_shuffle_epi32 (_low16, 0x08);     /*B000G000 G100R100 xxxxxxxx xxxxxxxx,  00 00 10 00=0x08*/        \
  _ig8     = _mm_shufflelo_epi16 (_low16_2, 0x21); /*G0xxxxxx G1xxxxxx xxxxxxxx xxxxxxxx,  00 10 00 01=0x21*/        \
  _ig8     = _mm_and_si128 (_ig8, _mask1);         /*G0000000 G1000000 00000000 00000000*/                           \
  _hi16_2  = _mm_shuffle_epi32 (_hi16, 0xD0);      /*xxxxxxxx xxxxxxxx B200G200 G300R300,  11 01 00 00=0xD0*/        \
  _hi16_2  = _mm_shufflehi_epi16 (_hi16_2, 0x21);  /*xxxxxxxx xxxxxxxx G2xxxxxx G3xxxxxx,  00 10 00 01=0x21*/        \
  _hi16_2  = _mm_and_si128 (_hi16_2, _mask2);      /*00000000 00000000 G2000000 G3000000*/                           \
  _ig8     = _mm_or_si128 (_ig8, _hi16_2);         /*G0000000 G1000000 G2000000 G3000000*/                           \
  /*B-------------------------------------------------------------------------------------------------------------*/ \
  _ib8    = _mm_shufflelo_epi16 (_low16, 0x30);  /*B0xxxxxx B1xxxxxx xxxxxxxx xxxxxxxx,  00 11 00 00=0x30*/          \
  _ib8    = _mm_and_si128 (_ib8, _mask1);        /*B0000000 B1000000 00000000 00000000*/                             \
  _hi16_2 = _mm_shuffle_epi32 (_hi16, 0x90);     /*xxxxxxxx xxxxxxxx B200G200 R200B300,  10 01 00 00=0x90*/          \
  _hi16_2 = _mm_shufflehi_epi16 (_hi16_2, 0x30); /*xxxxxxxx xxxxxxxx B2xxxxxx B3xxxxxx,  00 11 00 00=0x30*/          \
  _hi16_2 = _mm_and_si128 (_hi16_2, _mask2);     /*00000000 00000000 B2000000 B3000000*/                             \
  _ib8    = _mm_or_si128 (_ib8, _hi16_2);        /*B0000000 B1000000 B2000000 B3000000*/
#endif


#if !defined(SPLIT_RGB24_AVX2_DEFINE_REGS)
#define SPLIT_RGB24_AVX2_DEFINE_REGS                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
  const __m256i _permute32  = _mm256_setr_epi32 (0, 1, 2, 0, 3, 4, 5, 3);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            \
  const __m256i _permute_b8 = _mm256_setr_epi8 (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
    UUU_ICAST_UCHAR (0x00), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x03), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x06), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x09), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x00), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x03), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x06), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x09), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80)); \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
  const __m256i _permute_g8 = _mm256_setr_epi8 (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
    UUU_ICAST_UCHAR (0x01), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x04), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x07), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0A), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x01), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x04), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x07), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0A), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80)); \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
  const __m256i _permute_r8 = _mm256_setr_epi8 (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     \
    UUU_ICAST_UCHAR (0x02), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x05), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x08), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0B), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x02), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x05), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x08), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x0B), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80), UUU_ICAST_UCHAR (0x80));
#endif


#if !defined(SPLIT_RGB24_AVX2)
#define SPLIT_RGB24_AVX2(_reg_rgb24, _ir8, _ig8, _ib8)                                                                                           \
  _reg_rgb24 = _mm256_permutevar8x32_epi32 (_reg_rgb24, _permute32); /*BOG0R0B1 G1R1B2G2 R2B3G3R3 BxGxRxBx B4G4R4B5 G5R5B6G6 R6B7G7R7 BxGxRxBx*/ \
  _ir8       = _mm256_shuffle_epi8 (_reg_rgb24, _permute_r8);        /*RO000000 R1000000 R2000000 R3000000 R4000000 R5000000 R6000000 R7000000*/ \
  _ig8       = _mm256_shuffle_epi8 (_reg_rgb24, _permute_g8);        /*GO000000 G1000000 G2000000 G3000000 G4000000 G5000000 G6000000 G7000000*/ \
  _ib8       = _mm256_shuffle_epi8 (_reg_rgb24, _permute_b8);        /*BO000000 B1000000 B2000000 B3000000 B4000000 B5000000 B6000000 B7000000*/
#endif


#if !defined(SLOW_SPLIT_RGB24_SSE1)
#if defined(UUU_COMPILER_GNUC) || defined(UUU_COMPILER_CLANG)
#define SLOW_SPLIT_RGB24_SSE1(_reg_rgb24, _ir8, _ig8, _ib8)          \
  _ib8 = _mm_insert_epi32 (_ib8, _mm_extract_epi8 (_i128_1, 0), 0);  \
  _ib8 = _mm_insert_epi32 (_ib8, _mm_extract_epi8 (_i128_1, 3), 1);  \
  _ib8 = _mm_insert_epi32 (_ib8, _mm_extract_epi8 (_i128_1, 6), 2);  \
  _ib8 = _mm_insert_epi32 (_ib8, _mm_extract_epi8 (_i128_1, 9), 3);  \
  _ig8 = _mm_insert_epi32 (_ig8, _mm_extract_epi8 (_i128_1, 1), 0);  \
  _ig8 = _mm_insert_epi32 (_ig8, _mm_extract_epi8 (_i128_1, 4), 1);  \
  _ig8 = _mm_insert_epi32 (_ig8, _mm_extract_epi8 (_i128_1, 7), 2);  \
  _ig8 = _mm_insert_epi32 (_ig8, _mm_extract_epi8 (_i128_1, 10), 3); \
  _ir8 = _mm_insert_epi32 (_ir8, _mm_extract_epi8 (_i128_1, 2), 0);  \
  _ir8 = _mm_insert_epi32 (_ir8, _mm_extract_epi8 (_i128_1, 5), 1);  \
  _ir8 = _mm_insert_epi32 (_ir8, _mm_extract_epi8 (_i128_1, 8), 2);  \
  _ir8 = _mm_insert_epi32 (_ir8, _mm_extract_epi8 (_i128_1, 11), 3);
#else
#define SLOW_SPLIT_RGB24_SSE1(_reg_rgb24, _ir8, _ig8, _ib8) \
  _ib8.m128i_u32[0] = _i128_1.m128i_u8[0];                  \
  _ib8.m128i_u32[1] = _i128_1.m128i_u8[3];                  \
  _ib8.m128i_u32[2] = _i128_1.m128i_u8[6];                  \
  _ib8.m128i_u32[3] = _i128_1.m128i_u8[9];                  \
                                                            \
  _ig8.m128i_u32[0] = _i128_1.m128i_u8[1];                  \
  _ig8.m128i_u32[1] = _i128_1.m128i_u8[4];                  \
  _ig8.m128i_u32[2] = _i128_1.m128i_u8[7];                  \
  _ig8.m128i_u32[3] = _i128_1.m128i_u8[10];                 \
                                                            \
  _ir8.m128i_u32[0] = _i128_1.m128i_u8[2];                  \
  _ir8.m128i_u32[1] = _i128_1.m128i_u8[5];                  \
  _ir8.m128i_u32[2] = _i128_1.m128i_u8[8];                  \
  _ir8.m128i_u32[3] = _i128_1.m128i_u8[11];
#endif
#endif
