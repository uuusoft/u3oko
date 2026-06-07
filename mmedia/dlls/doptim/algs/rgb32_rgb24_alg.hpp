#pragma once
/**
\file       rgb32_rgb24_alg.hpp
\date       22.02.2026
\author     Erashov Anton erashov2026@proton.me erashov2004@yandex.ru
\project    u3_doptim_dll
*/

namespace dlls::doptim::impl::algs
{
class CRGB32_RGB24Alg final : public IOptimAlg
{
  public:
  static constexpr const char* val_key = "libs.optim.convert.rgb32_rgb24";

  CRGB32_RGB24Alg ()
  {
    sync_impl (::libs::optim::io::TInit ());
    sel_.set_algoritm_name (val_key);
  }

  virtual ~CRGB32_RGB24Alg () = default;

  protected:
  virtual void
  sync_impl_int (const ::libs::optim::io::TInit& info) override
  {
    sel_.set (::libs::optim::convert::rgb32_rgb24::alu);
  }
};
}   // namespace dlls::doptim::impl::algs
