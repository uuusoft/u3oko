#pragma once
/**
\file       rgb_to_hsl_int.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       24.11.2016
\project    u3_optim_convert
*/

namespace libs::optim::s16bit::convert::hsl_vs_rgb
{
inline bool
check_rgb2hsl (::libs::optim::io::MCallInfo& info)
{
  if (3 != info.dsts_.size ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  if (1 != info.srcs_.size ())
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  const ::libs::optim::io::ProxyBuf& h   = info.dsts_[0];
  const ::libs::optim::io::ProxyBuf& s   = info.dsts_[1];
  const ::libs::optim::io::ProxyBuf& l   = info.dsts_[2];
  const ::libs::optim::io::ProxyBuf& rgb = info.srcs_[0];

  if ((h.width_ != s.width_) || (h.width_ != l.width_) || (h.width_ != rgb.width_))
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  if ((h.height_ != s.height_) || (h.height_ != l.height_) || (h.height_ != rgb.height_))
  {
    U3_ASSERT_SIGNAL_NT ("failed");
    return false;
  }

  return true;
}
}   // namespace libs::optim::s16bit::convert::hsl_vs_rgb


#if !defined(RGB2HSL_PREFIX)
#  define RGB2HSL_PREFIX(size)                                                                                 \
                                                                                                               \
    U3_CHECK (check_rgb2hsl (info), "failde check rgb2hsl");                                                   \
    const std::uint32_t  ppc            = size;                                                                \
    const std::uint32_t  width          = info.srcs_[0].width_;                                                \
    const std::uint32_t  height         = info.srcs_[0].height_;                                               \
    std::int16_t*        h              = info.dsts_[0].buf ();                                                \
    std::int16_t*        s              = info.dsts_[1].buf ();                                                \
    std::int16_t*        l              = info.dsts_[2].buf ();                                                \
    const std::uint32_t* rgb24          = U3_CAST_REINTERPRET< const std::uint32_t* > (info.srcs_[0].ubuf ()); \
    const std::uint32_t  raw_cycle      = width / ppc;                                                         \
    const std::uint32_t  cycle          = (raw_cycle * ppc < width) ? raw_cycle + 1 : raw_cycle;               \
    const std::uint32_t  leak_rgb       = info.srcs_[0].stride_ - cycle * ppc * sizeof (std::uint8_t) * 3;     \
    const std::uint32_t  req_stride_hsl = cycle * sizeof (std::uint16_t) * ppc;                                \
    const std::uint32_t  leak_hsl       = info.dsts_[0].stride_ - req_stride_hsl;

#endif


#if !defined(SPLIT_RGB24_SSE2_DEFINE_REGS)
#  define SPLIT_RGB24_SSE2_DEFINE_REGS                             \
                                                                   \
    const __m128i zero = _mm_setzero_si128 ();                     \
    __m128i       low16;                                           \
    __m128i       low16_2;                                         \
    __m128i       hi16;                                            \
    __m128i       hi16_2;                                          \
    const __m128i mask1 = _mm_setr_epi32 (0xFF, 0xFF, 0x00, 0x00); \
    const __m128i mask2 = _mm_setr_epi32 (0x00, 0x00, 0xFF, 0xFF);
#endif


#if !defined(SPLIT_RGB24_SSE2)
#  define SPLIT_RGB24_SSE2(reg_rgb24, ir8, ig8, ib8)                                                                   \
                                                                                                                       \
    reg_rgb24 = _mm_shuffle_epi32 (reg_rgb24, 0x94); /*BOG0R0B1 G1R1B2G2 G1R1B2G2 R2B3G3R3,  10 01 01 00=0x94*/        \
    low16     = _mm_unpacklo_epi8 (reg_rgb24, zero); /*B000G000 R000B100 G100R100 B200G200*/                           \
    low16_2   = _mm_shuffle_epi32 (low16, 0xC9);     /*R000B100 G100R100 B000G000 B200G200,  11 00 10 01=0xc9*/        \
    /*R-------------------------------------------------------------------------------------------------------------*/ \
    ir8    = _mm_shufflelo_epi16 (low16_2, 0x30); /*R0xxxxxx R1xxxxxx xxxxxxxx xxxxxxxx,  00 11 00 00=0x30*/           \
    ir8    = _mm_and_si128 (ir8, mask1);          /*R0000000 R1000000 00000000 00000000*/                              \
    hi16   = _mm_unpackhi_epi8 (reg_rgb24, zero); /*G100R100 B200G200 R200B300 G300R300*/                              \
    hi16_2 = _mm_shufflehi_epi16 (hi16, 0x30);    /*xxxxxxxx xxxxxxxx R2xxxxxx R3xxxxxx,  00 11 00 00=0x30*/           \
    hi16_2 = _mm_and_si128 (hi16_2, mask2);       /*00000000 00000000 R2000000 R3000000*/                              \
    ir8    = _mm_or_si128 (ir8, hi16_2);          /*R0000000 R1000000 R2000000 R3000000*/                              \
    /*G-------------------------------------------------------------------------------------------------------------*/ \
    low16_2 = _mm_shuffle_epi32 (low16, 0x08);     /*B000G000 G100R100 xxxxxxxx xxxxxxxx,  00 00 10 00=0x08*/          \
    ig8     = _mm_shufflelo_epi16 (low16_2, 0x21); /*G0xxxxxx G1xxxxxx xxxxxxxx xxxxxxxx,  00 10 00 01=0x21*/          \
    ig8     = _mm_and_si128 (ig8, mask1);          /*G0000000 G1000000 00000000 00000000*/                             \
    hi16_2  = _mm_shuffle_epi32 (hi16, 0xD0);      /*xxxxxxxx xxxxxxxx B200G200 G300R300,  11 01 00 00=0xD0*/          \
    hi16_2  = _mm_shufflehi_epi16 (hi16_2, 0x21);  /*xxxxxxxx xxxxxxxx G2xxxxxx G3xxxxxx,  00 10 00 01=0x21*/          \
    hi16_2  = _mm_and_si128 (hi16_2, mask2);       /*00000000 00000000 G2000000 G3000000*/                             \
    ig8     = _mm_or_si128 (ig8, hi16_2);          /*G0000000 G1000000 G2000000 G3000000*/                             \
    /*B-------------------------------------------------------------------------------------------------------------*/ \
    ib8    = _mm_shufflelo_epi16 (low16, 0x30);  /*B0xxxxxx B1xxxxxx xxxxxxxx xxxxxxxx,  00 11 00 00=0x30*/            \
    ib8    = _mm_and_si128 (ib8, mask1);         /*B0000000 B1000000 00000000 00000000*/                               \
    hi16_2 = _mm_shuffle_epi32 (hi16, 0x90);     /*xxxxxxxx xxxxxxxx B200G200 R200B300,  10 01 00 00=0x90*/            \
    hi16_2 = _mm_shufflehi_epi16 (hi16_2, 0x30); /*xxxxxxxx xxxxxxxx B2xxxxxx B3xxxxxx,  00 11 00 00=0x30*/            \
    hi16_2 = _mm_and_si128 (hi16_2, mask2);      /*00000000 00000000 B2000000 B3000000*/                               \
    ib8    = _mm_or_si128 (ib8, hi16_2);         /*B0000000 B1000000 B2000000 B3000000*/
#endif


#if !defined(SPLIT_RGB24_AVX2_DEFINE_REGS)
#  define SPLIT_RGB24_AVX2_DEFINE_REGS                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
    const __m256i permute32  = _mm256_setr_epi32 (0, 1, 2, 0, 3, 4, 5, 3);                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                             \
    const __m256i permute_b8 = _mm256_setr_epi8 (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
      U3_CAST_UINT8 (0x00), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x03), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x06), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x09), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x00), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x03), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x06), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x09), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80)); \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
    const __m256i permute_g8 = _mm256_setr_epi8 (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
      U3_CAST_UINT8 (0x01), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x04), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x07), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0A), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x01), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x04), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x07), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0A), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80)); \
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                       \
    const __m256i permute_r8 = _mm256_setr_epi8 (                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                      \
      U3_CAST_UINT8 (0x02), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x05), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x08), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0B), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x02), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x05), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x08), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x0B), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80), U3_CAST_UINT8 (0x80));
#endif


#if !defined(SPLIT_RGB24_AVX2)
#  define SPLIT_RGB24_AVX2(reg_rgb24, ir8, ig8, ib8)                                                                                            \
    reg_rgb24 = _mm256_permutevar8x32_epi32 (reg_rgb24, permute32); /*BOG0R0B1 G1R1B2G2 R2B3G3R3 BxGxRxBx B4G4R4B5 G5R5B6G6 R6B7G7R7 BxGxRxBx*/ \
    ir8       = _mm256_shuffle_epi8 (reg_rgb24, permute_r8);        /*RO000000 R1000000 R2000000 R3000000 R4000000 R5000000 R6000000 R7000000*/ \
    ig8       = _mm256_shuffle_epi8 (reg_rgb24, permute_g8);        /*GO000000 G1000000 G2000000 G3000000 G4000000 G5000000 G6000000 G7000000*/ \
    ib8       = _mm256_shuffle_epi8 (reg_rgb24, permute_b8);        /*BO000000 B1000000 B2000000 B3000000 B4000000 B5000000 B6000000 B7000000*/
#endif


#if !defined(SLOW_SPLIT_RGB24_SSE1)
#  if defined(U3_COMPILER_GNUC) || defined(U3_COMPILER_CLANG)
#    define SLOW_SPLIT_RGB24_SSE1(reg_rgb24, ir8, ig8, ib8)           \
      ib8 = _mm_insert_epi32 (ib8, _mm_extract_epi8 (i128_1, 0), 0);  \
      ib8 = _mm_insert_epi32 (ib8, _mm_extract_epi8 (i128_1, 3), 1);  \
      ib8 = _mm_insert_epi32 (ib8, _mm_extract_epi8 (i128_1, 6), 2);  \
      ib8 = _mm_insert_epi32 (ib8, _mm_extract_epi8 (i128_1, 9), 3);  \
      ig8 = _mm_insert_epi32 (ig8, _mm_extract_epi8 (i128_1, 1), 0);  \
      ig8 = _mm_insert_epi32 (ig8, _mm_extract_epi8 (i128_1, 4), 1);  \
      ig8 = _mm_insert_epi32 (ig8, _mm_extract_epi8 (i128_1, 7), 2);  \
      ig8 = _mm_insert_epi32 (ig8, _mm_extract_epi8 (i128_1, 10), 3); \
      ir8 = _mm_insert_epi32 (ir8, _mm_extract_epi8 (i128_1, 2), 0);  \
      ir8 = _mm_insert_epi32 (ir8, _mm_extract_epi8 (i128_1, 5), 1);  \
      ir8 = _mm_insert_epi32 (ir8, _mm_extract_epi8 (i128_1, 8), 2);  \
      ir8 = _mm_insert_epi32 (ir8, _mm_extract_epi8 (i128_1, 11), 3);
#  else
#    define SLOW_SPLIT_RGB24_SSE1(reg_rgb24, ir8, ig8, ib8) \
      ib8.m128i_u32[0] = i128_1.m128i_u8[0];                \
      ib8.m128i_u32[1] = i128_1.m128i_u8[3];                \
      ib8.m128i_u32[2] = i128_1.m128i_u8[6];                \
      ib8.m128i_u32[3] = i128_1.m128i_u8[9];                \
                                                            \
      ig8.m128i_u32[0] = i128_1.m128i_u8[1];                \
      ig8.m128i_u32[1] = i128_1.m128i_u8[4];                \
      ig8.m128i_u32[2] = i128_1.m128i_u8[7];                \
      ig8.m128i_u32[3] = i128_1.m128i_u8[10];               \
                                                            \
      ir8.m128i_u32[0] = i128_1.m128i_u8[2];                \
      ir8.m128i_u32[1] = i128_1.m128i_u8[5];                \
      ir8.m128i_u32[2] = i128_1.m128i_u8[8];                \
      ir8.m128i_u32[3] = i128_1.m128i_u8[11];
#  endif
#endif
