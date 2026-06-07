#pragma once
/**
\file       freq_dct_b8x8_forward.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CFreqDCT8x8ForwardAlg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.freq.dct.b8x8.forward";

  CFreqDCT8x8ForwardAlg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CFreqDCT8x8ForwardAlg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::sse2);
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::alu);
      break;
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::alu);
#else
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::alu);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::freq::dct::b8x8::forward::alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
