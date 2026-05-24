#pragma once
/**
\file       average2x2.hpp
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\date       01.01.2017
\project    u3_doptim_dll
*/
// EAI-REMOVE old shit
namespace dlls::doptim::impl::algs
{
#if 0
class CAverage2x2Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key;

  CAverage2x2Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CAverage2x2Alg ()
  {
  }

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
#  if defined(U3_CPU_X86)
    case ::libs::helpers::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_avx2);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_avx1);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::sse4_2:
    case ::libs::helpers::sys::cpu::CpuExts::sse4_1:
    // case ::libs::helpers::sys::cpu::CpuExts::eecI64:
    case ::libs::helpers::sys::cpu::CpuExts::sse3:
    case ::libs::helpers::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_sse2);
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_alu);
      break;
#  endif
    case ::libs::helpers::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_alu);
      break;
    case ::libs::helpers::sys::cpu::CpuExts::usual:
#  if defined(U3_CPU_X86)
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_sse2);
#  elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_alu);
#  else
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_alu);
#  endif
      break;
#  if defined(U3_CPU_ARM)
    case ::libs::helpers::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_alu);
      break;
#  endif
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::s16bit::filter::jam::aver1_2x2_alu);
      break;
    }
  }
};
#endif
}   // namespace dlls::doptim::impl::algs
