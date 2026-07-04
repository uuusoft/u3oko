#pragma once
/**
\file       nv212y16.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CNV212Y16Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.convert.nv21_y16";

  CNV212Y16Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CNV212Y16Alg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::utility::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::convert::nv21_y16::avx2);
      break;
    case ::libs::utility::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::convert::nv21_y16::sse2);
      break;
    case ::libs::utility::sys::cpu::CpuExts::sse4_2:
    case ::libs::utility::sys::cpu::CpuExts::sse4_1:
    case ::libs::utility::sys::cpu::CpuExts::sse3:
    case ::libs::utility::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::convert::nv21_y16::sse2);
      break;
    case ::libs::utility::sys::cpu::CpuExts::sse1:
      sel_.set (::libs::optim::convert::nv21_y16::alu);
      break;
#endif
    case ::libs::utility::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::convert::nv21_y16::alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::convert::nv21_y16::sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::convert::nv21_y16::neon);
#else
      sel_.set (::libs::optim::convert::nv21_y16::alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::utility::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::convert::nv21_y16::neon);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::convert::nv21_y16::alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
