#pragma once
/**
\file       uyvy2y16.hpp
\author     Erashov Anton erashov2026@proton.me
\date       28.03.2026
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CUYVY2Y16Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.convert.uyvy_y16";

  CUYVY2Y16Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CUYVY2Y16Alg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& iinfo) override
  {
    switch (iinfo.ext_)
    {
    case ::libs::utility::sys::cpu::CpuExts::alu:
      sel_.set (::libs::optim::convert::uyvy_y16::alu);
      break;
    case ::libs::utility::sys::cpu::CpuExts::usual:
      sel_.set (::libs::optim::convert::uyvy_y16::alu);
      break;
    default:
      U3_ASSERT_SIGNAL_NT ("failed");
      sel_.set (::libs::optim::convert::uyvy_y16::alu);
      break;
    }
  }
};
}   // namespace dlls::doptim::impl::algs
