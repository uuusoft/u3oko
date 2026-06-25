#pragma once
/**
\file       l2rgb.hpp
\author     Erashov Anton erashov2026@proton.me
\date       21.11.2016
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CL2RgbAlg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.convert.l_vs_rgb.l_to_rgb24";

  CL2RgbAlg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CL2RgbAlg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse1:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
      break;
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
#else
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::convert::l_vs_rgb::l_to_rgb24_alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
