#pragma once
/**
\file       rgb2l2.hpp
\date       01.08.2017
\author     Erashov Anton erashov2026@proton.me
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CRgb2LAlg2 final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.convert.l_vs_rgb2.rgb24_to_l";

  CRgb2LAlg2 ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CRgb2LAlg2 ()
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
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_sse2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse1:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_sse1);
      break;
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#if defined(U3_CPU_X86)
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_neon);
#else
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_alu);
#endif
      break;
#if defined(U3_CPU_ARM)
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_neon);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb2::rgb24_to_l_alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
