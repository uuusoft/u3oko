#pragma once
/**
\file       count_if_ge_alg.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.05.2018
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CCountIfGEAlg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.statistics.count_if_ge";

  CCountIfGEAlg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CCountIfGEAlg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::sse2);
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::alu);
      break;
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::alu);
#else
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::alu);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::statistics::count_if_ge::alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
