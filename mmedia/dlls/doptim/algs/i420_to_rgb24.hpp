#pragma once
/**
\file       i420_to_rgb24.hpp
\author     Erashov Anton erashov2026@proton.me
\date       01.01.2017
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class I420ToRgb24Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.convert.i420_rgb24";

  I420ToRgb24Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
    sel_.set_block_align_x (8);
    sel_.set_block_align_y (8);
  }

  virtual ~I420ToRgb24Alg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
#ifdef U3_DISABLE_AS_0_FOR_CLANG_TIDY
    switch (iinfo.ext_)
    {
#  if defined(U3_CPU_X86)
    case ::libs::utility::sys::cpu::CpuExts::avx2:
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::avx1:
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::sse4_2:
    case ::libs::utility::sys::cpu::CpuExts::sse4_1:
    case ::libs::utility::sys::cpu::CpuExts::sse3:
    case ::libs::utility::sys::cpu::CpuExts::sse2:
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::sse1:
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
      break;
#  endif
    case ::libs::utility::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::usual:
#  if defined(U3_CPU_X86)
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
#  elif defined(U3_CPU_ARM)
      sel_.set (::libs::optim::convert::nv21_rgb24::neon);
#  else
      sel_.set (::libs::optim::convert::nv21_rgb24::alu);
#  endif
      break;
#  if defined(U3_CPU_ARM)
    case ::libs::utility::sys::cpu::CpuExts::neon:
      sel_.set (::libs::optim::convert::nv21_rgb24::neon);
      break;
#  endif
    default:
      U3_ASSERT_SIGNAL_NT ("libs.optim.convert.i420_rgb24 alu");
      sel_.set (libs::optim::convert::i420_rgb24::alu);
      break;
    }
#endif
    sel_.set (libs::optim::convert::i420_rgb24::alu);
  }
};
}   // namespace dlls::doptim::impl::algs
