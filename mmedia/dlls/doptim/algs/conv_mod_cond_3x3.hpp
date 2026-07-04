#pragma once
/**
\file       conv_mod_cond_3x3.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CConvModCond3x3Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.conv.mod_cond_b3x3";

  CConvModCond3x3Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CConvModCond3x3Alg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::utility::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_avx2);
      break;
    case ::libs::utility::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_avx1);
      break;
    case ::libs::utility::sys::cpu::CpuExts::sse4_2:
    case ::libs::utility::sys::cpu::CpuExts::sse4_1:
    case ::libs::utility::sys::cpu::CpuExts::sse3:
    case ::libs::utility::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_sse2);
      break;
#endif
    case ::libs::utility::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_alu);
#else
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::utility::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_alu);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::conv::cond::mod_cond_b3x3_alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
