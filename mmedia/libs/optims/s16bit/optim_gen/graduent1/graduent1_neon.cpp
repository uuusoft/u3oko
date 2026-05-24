/**
\file       graduent1_neon.cpp
\date       01.05.2017
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_optim_libs_gen
*/
#include "mmedia/includes/control-defines-includes.hpp"
#include "mmedia/includes/includes.hpp"
#include "mmedia/libs/optims/s16bit/optim_s16bit_generic/includes_int.hpp"
#include "graduent1.hpp"

#if defined(U3_CPU_ARM)

namespace libs::optim::s16bit::gen::graduent1
{
void
neon (::libs::optim::io::MCallInfo& cinfo)
{
  check (cinfo);

  const std::uint32_t  ppc    = 8;
  std::int16_t*        buf    = cinfo.dsts_[0].buf ();
  const std::uint32_t  stride = cinfo.dsts_[0].stride_;
  const std::uint32_t  width  = cinfo.dsts_[0].width_;
  const std::uint32_t  height = cinfo.dsts_[0].height_;
  const std::uint16_t* ivals  = U3_CAST_REINTERPRET< const std::uint16_t* > (cinfo.params_.consts_[0]);
  const std::uint32_t  leak   = stride - (width / ppc * ppc) * sizeof (std::int16_t);
  // const std::int32_t             size_ivals = cinfo.params_.ints_[0];

  U3_ASSERT (::libs::helpers::mem::check_align16_ptr (buf));
  U3_ASSERT (::libs::helpers::mem::check_align16 (stride));

  uint8x8x4_t table_0_31;
  uint8x8x4_t table_32_63;
  uint8x8x4_t table_64_95;
  uint8x8x4_t table_96_127;
  uint8x8x4_t table_128_159;
  uint8x8x4_t table_160_191;
  uint8x8x4_t table_192_223;
  uint8x8x4_t table_223_255;

  const std::uint32_t lpxs = 8;

#  define LOAD_PART_TABLE(mreg, moff)                                                                                                                           \
    mreg.val[0] = vmovn_u16 (vld1q_u16 (U3_CAST_REINTERPRET< const std::uint16_t* > (U3_CAST_REINTERPRET< const std::uint8_t* > (ivals + (0 + moff) * lpxs)))); \
    mreg.val[1] = vmovn_u16 (vld1q_u16 (U3_CAST_REINTERPRET< const std::uint16_t* > (U3_CAST_REINTERPRET< const std::uint8_t* > (ivals + (1 + moff) * lpxs)))); \
    mreg.val[2] = vmovn_u16 (vld1q_u16 (U3_CAST_REINTERPRET< const std::uint16_t* > (U3_CAST_REINTERPRET< const std::uint8_t* > (ivals + (2 + moff) * lpxs)))); \
    mreg.val[3] = vmovn_u16 (vld1q_u16 (U3_CAST_REINTERPRET< const std::uint16_t* > (U3_CAST_REINTERPRET< const std::uint8_t* > (ivals + (3 + moff) * lpxs))));

  LOAD_PART_TABLE (table_0_31, 0);
  LOAD_PART_TABLE (table_32_63, 4);
  LOAD_PART_TABLE (table_64_95, 8);
  LOAD_PART_TABLE (table_96_127, 12);
  LOAD_PART_TABLE (table_128_159, 16);
  LOAD_PART_TABLE (table_160_191, 20);
  LOAD_PART_TABLE (table_192_223, 24);
  LOAD_PART_TABLE (table_223_255, 28);

  const int16x8_t const32 = vdupq_n_s16 (32);

  for (std::uint32_t indxy = 0; indxy < height; ++indxy)
  {
    for (std::uint32_t indxx = 0; indxx < width; indxx += ppc)
    {
      int16x8_t data = vld1q_s16 (buf);
      uint8x8_t akk  = vdup_n_u8 (0);
      uint8x8_t fakk = vdup_n_u8 (0);
      uint8x8_t data8;

      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_0_31, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_32_63, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_64_95, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_96_127, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_128_159, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_160_191, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_192_223, data8);
      fakk  = vorr_u8 (akk, fakk);

      data  = vsubq_s16 (data, const32);
      data8 = vmovn_u16 (vreinterpretq_u16_s16 (data));
      akk   = vtbl4_u8 (table_223_255, data8);
      fakk  = vorr_u8 (akk, fakk);

      data = vreinterpretq_s16_u16 (vmovl_u8 (fakk));
      vst1q_s16 (buf, data);
      buf += ppc;
    }

    U3_FAST_MOVE_PTR (buf, leak);
  }
}
}   // namespace libs::optim::s16bit::gen::graduent1

#endif
