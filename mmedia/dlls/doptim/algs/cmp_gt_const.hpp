#pragma once
/**
\file       cmp_gt_const.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CCmpGTConstAlg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.s16bit.bits.cmp.gt_const";

  CCmpGTConstAlg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CCmpGTConstAlg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#ifdef U3_CPU_X86
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::sse2);
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse1:
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
      break;
#endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#ifdef U3_CPU_X86
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::sse2);
#elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
#else
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
#endif
      break;
#ifdef U3_CPU_ARM
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
      break;
#endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::bits::cmp::gt_const::alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
