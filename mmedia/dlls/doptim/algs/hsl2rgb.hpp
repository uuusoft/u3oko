#pragma once
/**
\file       hsl2rgb.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CHSL2RgbAlg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.convert.hsl_vs_rgb.hsl_to_rgb24";

  CHSL2RgbAlg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CHSL2RgbAlg ()
  {
  }

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#if defined(U3_CPU_X86)
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    // case ::libs::helpers::sys::cpu::CpuExts::eecI64:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_sse3);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_sse2);
      break;
#  if defined(U3_CPU_X86_32)
    case ::libs::helpers::sys::cpu::CpuExts::sse1:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_sse1);
      break;
#  endif
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#if defined(U3_CPU_X86)
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_neon);
#else
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_alu);
#endif
      break;
#if defined(U3_CPU_ARM)
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_neon);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::convert::hsl_vs_rgb::hsl_to_rgb24_alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
