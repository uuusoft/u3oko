#pragma once
/**
\file       remove_add_noise2.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CRemoveAddNoise2Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.filter.noise.var2";

  CRemoveAddNoise2Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CRemoveAddNoise2Alg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::filter::noise::var2::avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::filter::noise::var2::avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::filter::noise::var2::sse2);
      break;
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::filter::noise::var2::alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::s16bit::filter::noise::var2::sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::filter::noise::var2::alu);
#else
      sel_.set (::libs::optim::s16bit::filter::noise::var2::alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::filter::noise::var2::alu);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::filter::noise::var2::alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
